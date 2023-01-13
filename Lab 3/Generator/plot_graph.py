"""import the file"""
import ctypes
import sys
import networkx as nx
import matplotlib.pyplot as plt


def get_ppi():
    """
    > Get the PPI of the screen by calling the Windows API
    :return: The number of pixels per inch.
    """
    LOG_PIXELS_X = 88

    user32 = ctypes.windll.user32
    user32.SetProcessDPIAware()
    dc = user32.GetDC(0)
    pix_per_inch = ctypes.windll.gdi32.GetDeviceCaps(dc, LOG_PIXELS_X)

    user32.ReleaseDC(0, dc)
    return pix_per_inch


def main() -> None:
    """main function"""
    if len(sys.argv) < 2:
        print("argv error")
        sys.exit(-1)

    data_read = ""
    with open(file=sys.argv[1], mode="r") as file_open:
        data_read = file_open.readlines()

    data_read = [i.strip().split(" ") for i in data_read]
    nx_G = nx.Graph(name=sys.argv[1], weighted=True)

    edge = [list(map(int, i)) for i in data_read[1:]]
    nx_G.add_weighted_edges_from(edge)
    plt.tight_layout()

    # the graph layout
    pos = nx.spring_layout(nx_G)
    nx.draw_networkx(nx_G, pos)

    # show the edge weight
    edge_labels = nx.get_edge_attributes(nx_G, "weight")
    nx.draw_networkx_edge_labels(nx_G, pos, edge_labels=edge_labels)
    file_name = sys.argv[1].replace(".txt", "")
    plt.savefig(f"{file_name}_graph.png", dpi=get_ppi())
    plt.show()


if __name__ == "__main__":
    main()
