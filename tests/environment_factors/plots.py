import numpy as np
import matplotlib.pyplot as plt
from math import exp

def r_scalar(sla, shade, corrected=True):

    phi = 1.
    k = 1./6000.

    al = phi*exp(-k*sla)

    if shade == 'tolerant':
        r = 1 - exp(-4.64*(al-0.05))
    elif shade == 'intolerant':
        r = 2.24*(1 - exp(-1.136*(al-0.08)))

    if corrected:
        r = max(r,0)

    return r

r_vec = np.vectorize(r_scalar)


def t_scalar(degd, degd_min, degd_max, corrected=True):

    t = 4.*(degd-degd_min)*(degd_max-degd)/(degd_max-degd_min)**2

    if corrected:
        t = max(t,0.)

    return t

t_vec = np.vectorize(t_scalar)


def s_scalar(bar_soilq, corrected=True):

    # bar_soilq = bar/soilq
    s = 1 - bar_soilq
    if corrected:
        s = min(max(0., s), 1.)

    return s

s_vec = np.vectorize(s_scalar)


def plot_r_sla(corrected=True, save=False):

    sla = np.arange(0, 30000+1)
    r_tolerant = r_vec(sla, 'tolerant', corrected)
    r_intolerant = r_vec(sla, 'intolerant', corrected)
    
    title = 'Light extinction factor' + (' (not corrected)' if not corrected else '')
    fig, ax = plt.subplots(figsize=(5.5,4))
    ax.set_title(title)
    ax.plot(sla, r_tolerant, label='Tolerant', lw=2)
    ax.plot(sla, r_intolerant, label='Intolerant', lw=2)
    #ax.axhline(0, ls='--', color='gray')
    ax.grid()
    ax.axhline(0, lw=1, color='black')
    ax.axvline(0, lw=1, color='black')
    ax.set_xlabel('SLA')
    ax.set_ylabel('r')
    plt.legend()
    if save:
        cc = '_corr' if corrected else ''
        plt.savefig('plots/r' + cc + '.png', dpi=250)
    else:
        plt.show()


def plot_t_degd(corrected=True, save=False):

    degd_min = 2100.
    degd_max = 10700.
    dt = 500
    degd = np.arange(degd_min-dt,degd_max+dt+1)

    t_degd = t_vec(degd, degd_min, degd_max, corrected)
    
    title = 'Temperature regulation factor' + (' (not corrected)' if not corrected else '')
    fig, ax = plt.subplots(figsize=(5.5,4))
    ax.set_title(title)
    ax.plot(degd, t_degd, lw=2, label='White ash')
    #ax.axhline(0, ls='--', color='gray')
    #ax.axvline(degd_min, ls='--', color='gray')
    #ax.axvline(degd_max, ls='--', color='gray')
    ax.grid()
    ax.axhline(0, lw=1, color='black')
    ax.axvline(0, lw=1, color='black')
    ax.set_xlabel('Degree-days')
    ax.set_ylabel('t')
    plt.legend()
    if save:
        cc = '_corr' if corrected else ''
        plt.savefig('plots/t' + cc + '.png', dpi=250)
    else:
        plt.show()

    
def plot_s_bar_soilq(corrected=True, save=False):

    db = 0.2
    bar_soilq = np.linspace(0-db,1+db,1000)

    s_bar_soilq = s_vec(bar_soilq, corrected)

    title = 'Water and nutrients stress factor' + (' (corrected)' if corrected else '')
    fig, ax = plt.subplots(figsize=(5.5,4))
    ax.set_title(title)
    ax.plot(bar_soilq, s_bar_soilq)
    #ax.axhline(0, ls='--', color='gray')
    ax.axvline(0, ls='--', color='gray')
    ax.axvline(1, ls='--', color='gray')
    ax.grid()
    ax.axhline(0, lw=1, color='black')
    ax.axvline(0, lw=1, color='black')
    ax.set_xlabel('BAR/SOILQ')
    ax.set_ylabel('s')
    if save:
        cc = '_corr' if corrected else ''
        plt.savefig('plots/s' + cc + '.png', dpi=250)
    else:
        plt.show()


def plot_beer_lambert(save=True, units='jabowa'):

    if units == 'jabowa':
        lai = np.linspace(0,30000+1) # SLA
        phi = 1.
        k = 1./6000.
        xlabel = 'SLA'
        ylabel = 'AL'
    elif units == 'standard':
        lai = np.linspace(0,10)
        phi = 1.
        k = 0.5
        xlabel = 'LAI'
        ylabel = 'I/I0'
    else:
        print('Unknown units')
        return

    al = phi*np.exp(-k*lai)
    fig, ax = plt.subplots(figsize=(5.5,4))
    ax.set_title('Beer-Lambert law')
    ax.plot(lai, al)
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    plt.grid()
    plt.tight_layout()

    if save:
        plt.savefig('plots/beer_lambert_' + units + '.png', dpi=250)
    else:
        plt.show()


def main():

    plot_r_sla(corrected=False, save=True)
    plot_r_sla(corrected=True, save=True)
    
    plot_t_degd(corrected=False, save=True)
    plot_t_degd(corrected=True, save=True)

    plot_s_bar_soilq(corrected=False, save=True)
    plot_s_bar_soilq(corrected=True, save=True)

    plot_beer_lambert(save=True, units='jabowa')
    plot_beer_lambert(save=True, units='standard')

    return 0


if __name__ == '__main__':
    exit(main())


