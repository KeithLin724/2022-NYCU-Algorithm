# -*- coding: utf-8 -*-
'''
Title:Algorithm Lab 2 checker
Written By KYLiN
This is a code for Algorithm Lab 2 Checker
Date: 4/12/2022
'''

import sys
# https://shengyu7697.github.io/python-sys-argv/
# import pprint


def is_same_ans(res, resInv):
    """
    It reads the sample input file, calculates the distance between the two points in the list, sums up
    the distance between the two points in the list, and returns the result
    :param res: The list of points that you want to check
    :param resInv: The list of points that are the inverse of the original list
    """

    def distance_func(p1, p2) -> int:
        return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])

    # Reading the sample input file.
    try:
        with open(sys.argv[3], mode='r') as fSampleInput:
            dataSampleCase = fSampleInput.read()

    except FileNotFoundError as msg:
        print(msg)
        sys.exit()

    dataSampleCase = list(filter(lambda x: x != '',
                                 dataSampleCase.split('\n')))

    samplePointLen = int(dataSampleCase.pop(0))
    samplePointList = [
        list(map(int, elm.split(' ')))
        for elm in dataSampleCase[:samplePointLen]
    ]

    resList = [list(map(int, elm)) for elm in res]
    resInvList = [list(map(int, elm)) for elm in resInv]

    # Calculating the distance between the two points in the list.
    ansRes = [
        distance_func(samplePointList[elm[0]], samplePointList[elm[1]])
        for elm in resList
    ]
    ansResInv = [
        distance_func(samplePointList[elm[0]], samplePointList[elm[1]])
        for elm in resInvList
    ]

    # Summing up the distance between the two points in the list.
    sAnsRes = str(sum(ansRes))
    sAnsResInv = str(sum(ansResInv))

    return (list(map(str, ansRes)), list(map(str, ansResInv)), sAnsRes,
            sAnsResInv, (sAnsRes == sAnsResInv))


def main() -> None:
    if len(sys.argv) < 4:
        print('argument input format error')
        sys.exit()

    dataIn, dataCheck, dataSampleCase = '', '', ''
    try:
        with open(sys.argv[1], mode='r') as fSampleInput:
            dataIn = fSampleInput.read()

        with open(sys.argv[2], mode='r') as fCheckInput:
            dataCheck = fCheckInput.read()

    except FileNotFoundError as msg:
        print(msg)
        sys.exit()

    dataIn = list(filter(lambda x: x != '', dataIn.split('\n')))

    dataCheck = list(filter(lambda x: x != '', dataCheck.split('\n')))

    dataSampleCase = list(filter(lambda x: x != '',
                                 dataSampleCase.split('\n')))

    # check the data is same
    dataInLen, dataCheckLen = dataIn.pop(0), dataCheck.pop(0)

    dataInSet = set(frozenset(elm.split(' ')) for elm in dataIn)
    dataCheckSet = set(frozenset(elm.split(' ')) for elm in dataCheck)

    # pprint.pprint(samplePointList[0])

    if dataInLen != dataCheckLen:
        print(
            f"testcase: {sys.argv[1]} {sys.argv[2]} Not Same Length-> {dataIn} {dataCheckLen}"
        )
        sys.exit()

    # Checking if the data in the dataCheckSet is in the dataInSet. If it is not, it will add it to
    # the res set.
    res = dataCheckSet.difference(dataInSet)
    resInv = dataInSet.difference(dataCheckSet)

    # Replacing the .txt in the file name with a blank.
    fileName1, fileName2 = (sys.argv[1].replace('.txt', ''),
                            sys.argv[2].replace('.txt', ''))

    outputFileName = f'compare_{fileName1}_{fileName2}.txt'
    with open(outputFileName, mode='w') as fileOut:
        fPrint = fileOut.write
        if not res:
            print(f"test case: {sys.argv[1]} {sys.argv[2]} is Same~")
            fPrint(f"test case: {sys.argv[1]} {sys.argv[2]} is Same~\n")
        else:
            resAnsList, resInvAnsList, resAns, resInvAns, isSame = is_same_ans(
                res, resInv)

            displayStrSame = "Same" if isSame else "Not Same"

            print(
                f"test case: {sys.argv[1]} {sys.argv[2]} Not Same Path Set, {displayStrSame} Ans -> detail {outputFileName}"
            )

            fPrint(
                f"test case: {sys.argv[1]} {sys.argv[2]} Not Same Path Set\n")

            fPrint(f"\ndifferent {fileName2} -> {fileName1}\n")

            fPrint('\n'.join([
                f'{str(set(elm[0]))} => distance is {elm[1]}'
                for elm in zip(res, resAnsList)
            ]))

            fPrint(f'\ntotal : {resAns}\n')

            fPrint(f"\ndifferent {fileName1} -> {fileName2}\n")

            fPrint('\n'.join([
                f'{str(set(elm[0]))} => distance is {elm[1]}'
                for elm in zip(resInv, resInvAnsList)
            ]))

            fPrint(f'\ntotal: {resInvAns}\n')

            # A list comprehension. It is a way to create a list in a single line.
            resUsingPoint = [elm for item in res for elm in item]
            resInvUsingPoint = [elm for item in resInv for elm in item]

            # Sorting the list of points in ascending order.
            resUsingPoint = sorted(resUsingPoint, key=lambda x: int(x))
            resInvUsingPoint = sorted(resInvUsingPoint, key=lambda x: int(x))

            # Writing the result to the file.
            fPrint(f'\n{fileName2} using point\n')
            fPrint(' '.join(resUsingPoint) + '\n')

            fPrint(f'\n{fileName1} using point\n')
            fPrint(' '.join(resInvUsingPoint) + '\n')

            samePoint = set(resUsingPoint).intersection(set(resInvUsingPoint))
            samePoint = sorted(list(samePoint), key=lambda x: int(x))

            fPrint(f'\n{fileName2} {fileName1} same point\n')
            fPrint(' '.join(samePoint) + '\n')

            fPrint(f'\nIs same answer => {isSame}')
            # print(is_same_ans(res, resInv))


if __name__ == '__main__':
    main()
