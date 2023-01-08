# This is a code for the check NYCU Algorithm Lab2 sample code

## Written by KYLiN

---

using python 3 to write

### How to use

write cmd in console -> `python3 corrector_Lab2.py`

example

```
python3 corrector_Lab2.py golden1.txt testOut.txt case1.txt
```

if two file is not same will output compare file

File Name is 'compare\_\[file1\]\_\[file2\].txt'
inside like this example

```
test case: golden4.txt output4_1.txt Not Same Path Set

different output4_1 -> golden4
{'1909', '2758'} => distance is 131
{'68', '2784'} => distance is 239
{'2097', '1401'} => distance is 179
{'2620', '745'} => distance is 324
{'2812', '1925'} => distance is 59
total : 932

different golden4 -> output4_1
{'935', '2812'} => distance is 59
{'68', '2727'} => distance is 239
{'1905', '1401'} => distance is 179
{'2758', '1679'} => distance is 131
{'2228', '745'} => distance is 324
total: 932

output4_1 using point
68 745 1401 1909 1925 2097 2620 2758 2784 2812

golden4 using point
68 745 935 1401 1679 1905 2228 2727 2758 2812

output4_1 golden4 same point
68 745 1401 2758 2812

Is same answer => True

```

---

# Pattern Code

## How to use

write cmd in console -> `python3 pattern.py`

example

```
python3 pattern.py testCase.txt 5 3
```

sample output

```
5
3957 7487
7769 9714
3981 5984
5557 9425
7536 2954
2 3
2 1
4 2
```
