#!/usr/bin/env bash
# usage: ./test.sh [runs] [flags...]   e.g. ./test.sh 50 --complex
RUNS=${1:-20}; shift
CHECKER=./checker/ubuntu_checker
[[ "$(uname)" == "Darwin" ]] && CHECKER=./test/checker.py
for n in 3 5 100 500; do
	min=999999; max=0; tot=0; ko=0
	for ((i = 0; i < RUNS; i++)); do
		ARG=$(shuf -i 0-99999 -n "$n" | tr '\n' ' ')
		OUT=$(./push_swap "$@" $ARG)
		c=$(printf '%s' "$OUT" | grep -c .)
		[[ "$(printf '%s\n' "$OUT" | grep . | $CHECKER $ARG)" == "OK" ]] || ko=$((ko + 1))
		((c < min)) && min=$c; ((c > max)) && max=$c; tot=$((tot + c))
	done
	printf "n=%-4s min=%-6s avg=%-6s max=%-6s KO=%s\n" "$n" "$min" "$((tot / RUNS))" "$max" "$ko"
done