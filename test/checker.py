#!/usr/bin/env python3
"""independent push_swap checker: ./checker.py 3 2 1 < ops  -> OK / KO / Error"""
import sys

def main():
    try:
        a = [int(x) for x in sys.argv[1:]]
    except ValueError:
        sys.exit(print("Error", file=sys.stderr) or 1)
    if len(set(a)) != len(a) or any(v > 2**31 - 1 or v < -2**31 for v in a):
        sys.exit(print("Error", file=sys.stderr) or 1)
    b = []
    sw = lambda s: s.__setitem__(slice(0, 2), s[1::-1]) if len(s) > 1 else None
    ro = lambda s: s.append(s.pop(0)) if s else None
    rr = lambda s: s.insert(0, s.pop()) if s else None
    ops = {
        "sa": lambda: sw(a), "sb": lambda: sw(b), "ss": lambda: (sw(a), sw(b)),
        "pa": lambda: b and a.insert(0, b.pop(0)), "pb": lambda: a and b.insert(0, a.pop(0)),
        "ra": lambda: ro(a), "rb": lambda: ro(b), "rr": lambda: (ro(a), ro(b)),
        "rra": lambda: rr(a), "rrb": lambda: rr(b), "rrr": lambda: (rr(a), rr(b)),
    }
    for line in sys.stdin.read().split("\n"):
        if line == "":
            continue
        if line not in ops:
            sys.exit(print("Error", file=sys.stderr) or 1)
        ops[line]()
    print("OK" if not b and a == sorted(a) else "KO")

main()