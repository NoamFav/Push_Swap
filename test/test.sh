#!/usr/bin/env bash
# push_swap tester
# usage: ./test/test.sh [runs] [--leaks] [push_swap flags...]
#   ./test/test.sh                 20 runs per size, default strategy
#   ./test/test.sh 100 --complex   100 runs, forced strategy
#   ./test/test.sh 5 --leaks       also run valgrind / leaks on a few cases
# worst inputs and KO inputs are saved in test/logs/ to replay them

make
cd "$(dirname "$0")/.." || exit 1
PS=./push_swap
CHECKER=./test/checker.py
LOGS=test/logs
RUNS=20
LEAKS=0
FLAGS=()
for arg in "$@"; do
    case $arg in
    --leaks) LEAKS=1 ;;
    '' | *[!0-9]*) FLAGS+=("$arg") ;;
    *) RUNS=$arg ;;
    esac
done

if [[ -t 1 ]]; then
    GOLD=$'\e[1;38;5;220m' GREEN=$'\e[32m' ORANGE=$'\e[38;5;208m'
    RED=$'\e[1;31m' DIM=$'\e[2m' BOLD=$'\e[1m' RST=$'\e[0m'
fi
FAILS=0
TMP=$(mktemp)
trap 'rm -f "$TMP"' EXIT

mkdir -p "$LOGS"

# grade <n> <ops>  -> sets COL and LAB
grade() {
    local exc good pass
    case $1 in
    3) exc=3 good=3 pass=3 ;;
    5) exc=12 good=12 pass=12 ;;
    100) exc=699 good=1499 pass=1999 ;;
    500) exc=5499 good=7999 pass=11999 ;;
    1000) exc=12999 good=16999 pass=25999 ;;
    *) COL=$RST LAB="" && return ;;
    esac
    if (($2 <= exc)); then
        COL=$GOLD LAB=EXCELLENT
    elif (($2 <= good)); then
        COL=$GREEN LAB=GOOD
    elif (($2 <= pass)); then
        COL=$ORANGE LAB=PASS
    else COL=$RED LAB=FAIL; fi
}

title() { printf '\n%s── %s ──%s\n' "$BOLD" "$1" "$RST"; }

# ---------------------------------------------------------------- sorting
title "sorting  (${RUNS} runs/size${FLAGS[*]:+, ${FLAGS[*]}})"
for n in 3 5 100 500 1000; do
    min=999999 max=0 tot=0 ko=0
    : >"$LOGS/ko_$n.txt"
    for ((i = 0; i < RUNS; i++)); do
        read -ra ARG <<<"$(shuf -i 0-99999 -n "$n" | tr '\n' ' ')"
        OUT=$("$PS" "${FLAGS[@]}" "${ARG[@]}")
        c=$(printf '%s' "$OUT" | grep -c .)
        if [[ "$(printf '%s\n' "$OUT" | grep . | "$CHECKER" "${ARG[@]}")" != OK ]]; then
            ko=$((ko + 1))
            echo "${ARG[*]}" >>"$LOGS/ko_$n.txt"
        fi
        ((c < min)) && min=$c
        ((c > max)) && {
            max=$c
            echo "${ARG[*]}" >"$LOGS/worst_$n.txt"
        }
        tot=$((tot + c))
    done
    avg=$((tot / RUNS))
    line=$(printf 'n=%-4s' "$n")
    for v in "$min" "$avg" "$max"; do
        grade "$n" "$v"
        line+=$(printf ' %s%6s%s' "$COL" "$v" "$RST")
    done
    grade "$n" "$max"
    verdict="$COL$LAB$RST"
    [[ $LAB == FAIL ]] && FAILS=$((FAILS + 1))
    if ((ko > 0)); then
        verdict="${RED}KO x$ko${RST}  ${DIM}→ $LOGS/ko_$n.txt${RST}"
        FAILS=$((FAILS + 1))
    fi
    printf '%s   %s\n' "$line" "$verdict"
done
printf '%s       min    avg    max   verdict on worst case%s\n' "$DIM" "$RST"

# ---------------------------------------------------------------- errors
title "errors"
# expect <Error|silent> <label> [args...]
expect() {
    local want=$1 label=$2 out err
    shift 2
    out=$("$PS" "$@" 2>"$TMP")
    err=$(cat "$TMP")
    if [[ $want == Error && -z $out && $err == Error ]] ||
        [[ $want == silent && -z $out && -z $err ]]; then
        printf '  %s✓%s %s\n' "$GREEN" "$RST" "$label"
    else
        printf '  %s✗ %s%s  %sgot stdout=[%s] stderr=[%s]%s\n' \
            "$RED" "$label" "$RST" "$DIM" "${out//$'\n'/ }" "$err" "$RST"
        FAILS=$((FAILS + 1))
    fi
}
expect Error 'letters' 1 a 3
expect Error 'lone minus' -
expect Error 'lone plus' +
expect Error 'empty arg' ''
expect Error 'INT_MAX + 1' 2147483648
expect Error 'INT_MIN - 1' -2147483649
expect Error 'huge number' 99999999999999999999
expect Error 'duplicate' 4 2 4
expect Error '0 and -0' 0 -0
expect Error 'unknown flag' --nope 1 2
expect silent 'no args'
expect silent 'flags only' --bench
expect silent 'single number' 42
expect silent 'already sorted' -5 0 3 7 2147483647
expect silent 'INT_MIN..INT_MAX' -2147483648 2147483647

# ---------------------------------------------------------------- leaks
if ((LEAKS)); then
    title "leaks"
    if command -v valgrind >/dev/null; then
        LEAKCMD=(valgrind -q --leak-check=full --errors-for-leak-kinds=definite --error-exitcode=42)
    elif command -v leaks >/dev/null; then
        LEAKCMD=(leaks --atExit --)
    else
        LEAKCMD=()
        echo "  ${ORANGE}no valgrind or leaks found, skipped${RST}"
    fi
    if ((${#LEAKCMD[@]})); then
        for args in "3 2 1" "$(shuf -i 0-9999 -n 100 | tr '\n' ' ')" "1 a" "4 2 4" "--bench"; do
            read -ra ARG <<<"$args"
            "${LEAKCMD[@]}" "$PS" "${FLAGS[@]}" "${ARG[@]}" >"$TMP" 2>&1
            code=$?
            # valgrind exits 42 on a leak; leaks prints its own verdict.
            # push_swap's own exit 1 on Error is not a leak
            if [[ ${LEAKCMD[0]} == valgrind && $code -ne 42 ]] ||
                [[ ${LEAKCMD[0]} == leaks && $(cat "$TMP") == *" 0 leaks for 0 total"* ]]; then
                printf '  %s✓%s %s\n' "$GREEN" "$RST" "${args:0:30}"
            else
                printf '  %s✗ leak / memory error%s %s\n' "$RED" "$RST" "${args:0:30}"
                FAILS=$((FAILS + 1))
            fi
        done
    fi
fi

# ---------------------------------------------------------------- summary
echo
if ((FAILS == 0)); then
    echo "${GOLD}all clear${RST}"
else
    echo "${RED}${FAILS} problem(s)${RST}"
fi
exit $((FAILS > 0))
