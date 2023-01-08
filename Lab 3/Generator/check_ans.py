"""
Title:Lab 3 Checker
Written By KYLiN
This is a code for you to check you path is it work
Date: 31/12/2022
"""

import sys


class Checker:
    INIT_VAL = -1

    def __init__(self) -> None:
        self.__nodeNumber: int = 0
        self.__edgeNumber: int = 0

        self.__adjMatrix = dict()

        # check data

        self.__pathList: list[int] = []
        self.__pathCost: int = 0
        self.__fileName: tuple[str] = tuple()

    def read_file(self, fileNameCheck: str, fileNameSample: str) -> None:
        """
        It reads in two files, one containing a graph and the other containing a path and its cost
        
        :param fileNameCheck: str, fileNameSample: str
        :type fileNameCheck: str
        :param fileNameSample: the file name of the sample data
        :type fileNameSample: str
        """
        dataInCheck, dataSample = "", ""
        self.__fileName = (fileNameCheck, fileNameSample)
        try:

            with open(file=fileNameCheck, mode="r") as fInCheck, open(
                file=fileNameSample, mode="r"
            ) as fInSample:
                dataSample = fInSample.readlines()
                dataInCheck = fInCheck.readlines()
        except FileExistsError:
            print("No these file")
            sys.exit(-1)

        dataSample = list(map(lambda i: i.strip(), dataSample))

        self.__nodeNumber, self.__edgeNumber = list(map(int, dataSample[0].split(" ")))

        self.__adjMatrix = [
            [Checker.INIT_VAL for _ in range(self.__nodeNumber)]
            for _ in range(self.__nodeNumber)
        ]

        for dataStr in dataSample[1:]:
            a, b, length = list(map(int, dataStr.split(" ")))
            self.__adjMatrix[a][b] = length
            self.__adjMatrix[b][a] = length

        dataInCheck: list[str] = list(map(lambda i: i.strip(), dataInCheck))
        if dataInCheck[0] == "No":
            print(f"Case :{self.__fileName}")
            print("can not to check\n")
            sys.exit(-1)

        numberLst = dataInCheck[1].replace("Path:", "").strip().split(" ")
        self.__pathList = list(map(int, numberLst))

        self.__pathCost = int(dataInCheck[2].replace("Cost:", " "))

    def run_it(self) -> None:
        """
        It checks if the path is valid by checking if the number of nodes in the path is the same as the
        number of nodes in the graph, and if the path is a cycle
        :return: The return value is a list of lists.
        """
        self.__pathList.pop(-1)

        sizeSet = len(set(self.__pathList))
        if sizeSet != self.__nodeNumber:
            print(f"Node number is not same {sizeSet} != {self.__nodeNumber}\n")
            return

        if len(self.__pathList) != sizeSet:
            print("Node have same\n")
            return

        calCost: int = 0
        lstSz = len(self.__pathList)
        print(f"Case :{self.__fileName}\n")
        for i, val in enumerate(self.__pathList):
            disNum = self.__adjMatrix[val][self.__pathList[(i + 1) % lstSz]]

            if disNum == Checker.INIT_VAL:
                print("path is not work\n")
                return

            calCost += disNum

        print(f"Check number :{calCost}")
        print(f"file Cost number :{self.__pathCost}")
        print(f"is same {calCost == self.__pathCost}\n")


def main() -> None:

    if len(sys.argv) < 2:
        print("error input")
        sys.exit(-1)

    checker = Checker()
    checker.read_file(sys.argv[1], sys.argv[2])
    checker.run_it()


if __name__ == "__main__":
    main()
