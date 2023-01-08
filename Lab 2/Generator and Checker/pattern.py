import sys
from random import randrange, randint
'''
Title:KYLiN
Written By Pattern
This is a code for Algorithm code
It will generate the test case
Date: 4/12/2022
'''


def main() -> None:
    if (len(sys.argv) < 4):
        print("error format input")
        sys.exit()

    outputFileName, nodeNum, edgeNum = (sys.argv[1], int(sys.argv[2]),
                                        int(sys.argv[3]))
    setPoint = set()

    if (edgeNum > nodeNum - 1):
        print("error edge number > node number -1")
        sys.exit()

    while (len(setPoint) != nodeNum):
        setPoint.add((str(randrange(0, 10000)), str(randrange(0, 10000))))

    print(setPoint)

    edgeSet, havePoint = set(), set()

    while len(edgeSet) != edgeNum:

        a = str(randint(0, nodeNum - 1))
        b = str(randint(0, nodeNum - 1))
        while a == b:
            b = str(randint(0, nodeNum - 1))
        print(a, b)
        pointSet = frozenset([a, b])
        if a not in havePoint or b not in havePoint:
            edgeSet.add(pointSet)
            havePoint.add(a)
            havePoint.add(b)

    print(edgeSet)
    # for y in range(0 , nodeNum)
    with open(outputFileName, mode='w') as fOutput:
        fOutput.write(f'{nodeNum}\n')
        fOutput.write('\n'.join([' '.join(elm) for elm in setPoint]))
        fOutput.write('\n')
        fOutput.write('\n'.join([' '.join(elm) for elm in edgeSet]))


if __name__ == '__main__':
    main()
