import numpy as np
import matplotlib.pyplot as plt
from sys import argv

FNAME = "../out.txt"
NYEARS = 500
NPLOTS = 100
FOREST_SHAPE = (10,10)
NUMBER_OF_TREES = 0
WEIGHT = 1
BASAL_AREA = 2


def get_data(fname, nyears, nplots):

    with open(fname) as f:
        header = f.readline()
        header = header.split("|")[2:-1]
        header = [name.strip() for name in header]
    data = np.loadtxt(fname, skiprows=2)[:,1:] # remove 'year' column
    data = data.reshape([nyears, nplots, data.shape[1]])

    return header, data


def spatial_plots(data, year, forest_shape):

    density = data[year,:,1]
    density = density.reshape(forest_shape)
    print(density.shape)
    plt.imshow(density, origin='lower', cmap='YlGn')
    plt.show()


def plot_density(data, plot, year_range):

    density = data[slice(*year_range),plot,1]
    plt.plot(density)
    plt.show()


def forest_density(data, year_range, column):

    plot = 0
    density = data[slice(*year_range),plot,column]
    plt.plot(density)

    nyears = year_range[1] - year_range[0]
    density = data[slice(*year_range),:,column].mean(1)
    plt.plot(density)
    plt.show()


def main():

    header, data = get_data(FNAME, NYEARS, NPLOTS)
    #year = 350
    #spatial_plots(data, year, FOREST_SHAPE)
    year_range = (0,500)
    #plot = 0
    #plot_density(data, plot, year_range)
    forest_density(data, year_range, column=NUMBER_OF_TREES)


if __name__ == '__main__':
    exit(main())
