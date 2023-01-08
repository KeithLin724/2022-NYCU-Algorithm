import sys
import random

MIN_VAL, MAX_VAL = 1, 1000


def main() -> None:

    if len(sys.argv) < 3:
        print("arg error")
        sys.exit(-1)

    nodeNumber, fileOutName = int(sys.argv[1]), sys.argv[2]

    adjMatrix = [[random.randint(MIN_VAL, MAX_VAL) for _ in range(nodeNumber)]
                 for _ in range(nodeNumber)]

    edgeNumber = (nodeNumber * (nodeNumber - 1)) // 2

    print("open file")
    with open(file=fileOutName, mode='w') as fOpen:

        fOpen.write(' '.join(map(str, [nodeNumber, edgeNumber])) + '\n')

        for i, valArr in enumerate(adjMatrix[:nodeNumber - 1]):
            for j, val in enumerate(valArr[i + 1:]):
                fOpen.write(' '.join(map(str, [i, j + i + 1, val])) + '\n')


if __name__ == '__main__':
    main()
