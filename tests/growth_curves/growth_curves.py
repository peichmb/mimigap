import numpy as np
import matplotlib.pyplot as plt
import os

def read_data(fname):

    with open(fname) as f:
        all_lines = f.readlines()
        nlines = len(all_lines)
        starts = [(i,line) for i, line in enumerate(all_lines) if '*' in line]
        istarts = [i for i, line in starts]
        istarts.append(2*nlines)
        data = { pft:{} for pft,_ in enumerate(starts) }
        for pft, (i, line) in enumerate(starts):
            bits = line.split()
            data[pft]['name'] = ' '.join(bits[1:-3])
            data[pft]['max_d'] = float(bits[-3])
            data[pft]['max_h'] = float(bits[-2])
            data[pft]['max_age'] = float(bits[-1])

        for pft, (i, j) in enumerate(zip(istarts[:-1], istarts[1:])):
            gcs = [[float(x) for x in line.split()] for line in all_lines[i+1:j]]
            gcs = np.array(gcs)
            gc_d, gc_h, gc_w, gc_b = gcs[:,1], gcs[:,2], gcs[:,3], gcs[:,4]
            data[pft]['growth_curve_d'] = gc_d
            data[pft]['growth_curve_h'] = gc_h
            data[pft]['growth_curve_w'] = gc_w
            data[pft]['growth_curve_b'] = gc_b

    return data


def plot_growth_curve(ipft, data_pft):

    fig, ax = plt.subplots(2,2, figsize=(9,7))
    fig.suptitle('Growth curves for ' + data_pft['name'])
    ax[0,0].axvline(data_pft['max_age'], ls='--', label='Max Age', color='red')
    ax[0,0].plot(data_pft['growth_curve_d'])
    ax[0,0].axhline(data_pft['max_d'], ls='--', label='Max Diameter', color='gray')
    ax[0,0].set_xlabel('Age')
    ax[0,0].set_ylabel('Diameter (cm)')
    ax[0,0].legend(loc=2)
    ax[0,0].grid()
    ax[0,0].axvline(0,color='black')
    ax[0,0].axhline(0,color='black')
    ax[0,1].plot(data_pft['growth_curve_h'])
    ax[0,1].axvline(data_pft['max_age'], ls='--', label='Max Age', color='red')
    ax[0,1].axhline(data_pft['max_h'], ls='--', label='Max Height', color='gray')
    ax[0,1].set_xlabel('Age')
    ax[0,1].set_ylabel('Height (cm)')
    ax[0,1].legend(loc=2)
    ax[0,1].grid()
    ax[0,1].axvline(0,color='black')
    ax[0,1].axhline(0,color='black')
    ax[1,0].plot(data_pft['growth_curve_w'])
    ax[1,0].axvline(data_pft['max_age'], ls='--', label='Max Age', color='red')
    ax[1,0].set_xlabel('Age')
    ax[1,0].set_ylabel('Weight (C*D^2)')
    ax[1,0].legend(loc=2)
    ax[1,0].grid()
    ax[1,0].axvline(0,color='black')
    ax[1,0].axhline(0,color='black')
    ax[1,1].plot(data_pft['growth_curve_b'])
    ax[1,1].axvline(data_pft['max_age'], ls='--', label='Max Age', color='red')
    ax[1,1].set_xlabel('Age')
    ax[1,1].set_ylabel('Basal area (cm^2)')
    ax[1,1].legend(loc=2)
    ax[1,1].grid()
    ax[1,1].axvline(0,color='black')
    ax[1,1].axhline(0,color='black')
    plt.tight_layout()
    #plt.show()
    plt.savefig('plots/growth_curves_' + str(ipft).rjust(2,'0') + '.png')


def main():

    # Compile and run growth_curves.cpp
    os.system('c++ -o growth_curves.x -I../../src ../../src/gap.cpp growth_curves.cpp')
    os.system('./growth_curves.x > growth_curves.txt')

    # Compile data
    data_pfts = read_data('growth_curves.txt')

    # Make plots
    os.system('mkdir plots')
    for ipft, data in data_pfts.items():
        plot_growth_curve(ipft, data)

    # Remove junk
    os.system('rm growth_curves.x growth_curves.txt')

    return 0


if __name__ == '__main__':
    exit(main())
