# Diego Gomez, 2018
# Plot evolution of prior normal disribution under
# Bayesian inference
#####################################################################
#
#                               Libraries
#
#####################################################################
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib as mpl

#####################################################################
#
#                               Methods
#
#####################################################################
def gaussian_func(x, mu, gamma):
    return np.exp(-gamma*(x-mu)**2/2.0)*(gamma/(2.0*np.pi))**0.5

def plot_gaussians(list, m, g):
    xx = np.linspace(-3.0, 8., 1000)
    mpl.style.use('Solarize_Light2')
    fig, ax = plt.subplots(2,1,figsize=(18, 9))

    fig.suptitle(r'Normal prior evolution under Bayesian inference')

    for number in list:
        yy = gaussian_func(xx, m[number], g[number])
        label = str(number)
        ax[0].plot(xx, yy, label=r'$N=$'+label)
    ax[0].set_xlabel(r'$\mu$')
    ax[0].set_ylabel(r'$p(\mu)$')
    ax[0].legend()

    N = np.linspace(0, len(m)-1, len(m))
    ref = mu_star*np.ones(len(m))
    sigma = g**(-0.5)
    mp = m + sigma
    mm = m - sigma
    ax[1].plot(N, ref, label = r'$\mu^*$', c = 'r')
    ax[1].plot(N, m, label = r'$m$', c = 'g')
    ax[1].fill_between(N, mp, mm, facecolor = 'g', alpha=0.5)
    ax[1].set_xlabel(r'$N$ (# of points)')
    ax[1].set_ylabel(r'$m$')
    ax[1].legend(loc = 'lower center')

    plt.savefig('evolution.png', dpi = 200)
    plt.close()

#####################################################################
#
#                               Variables
#
#####################################################################
DataFrame_results = pd.read_csv("results.csv")
results = DataFrame_results.get_values()

m = results[:,0]
g = results[:,1]
x = results[:-1,2]

list = [0,1,4,9,16,25,36,50]
mu_star = 3.6843

#####################################################################
#
#                               Main Body
#
#####################################################################
plot_gaussians(list, m, g)
