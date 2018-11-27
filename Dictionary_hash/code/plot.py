import re
import csv
import numpy as np
import math
import scipy.io as sio
import os
import timeit
import matplotlib
import collections
import matplotlib.pyplot as plt
from sys import argv, exit, stdout
from numpy import linalg as la
# from dictionary_oa import *
# import dictionary_chain as chain
import argparse

methods = ['open addressing', 'chaining']
books = ['goneWithTheWind', 'theCountOfMonteCristo']

for book in books:

    filename = '/Users/messi/Documents/ISE407/HW5/' + book + '.txt'  # goneWithTheWind.txt
    file = open(filename, 'rt')
    text = file.read()
    file.close()
    # split based on words only
    words = re.sub(r'[0-9]+', '', text)
    words = re.split(r'\W+', words)

    num_words = len(words)
    print 'total words number is', num_words

    word_freq = {}
    for word in words:
        if word not in word_freq:
            word_freq[word] = 0
        word_freq[word] += 1
    num_items = len(word_freq.keys())
    print 'num of distinct words is', num_items  # Need to know the number of distinct words

    iid = 0
    for method in methods:
        if method == 'open addressing':
            from dictionary_oa import *
        else:
            from dictionary_chain import *

        iid = iid + 1

        @print_timing  #
        def test1(load_factor=0.5):
            dict_size = int(num_items / load_factor)
            word_count = Dict(dict_size)
            counts['compare'] = 0
            for word in words:
                if word not in word_count:
                    word_count[word] = 0
                word_count[word] += 1
            print 'Number of comparison using load factor %f is %d: ' % (load_factor, counts['compare'])
            return counts['compare']

        mytimes = {}
        mycounts = {}
        if method == 'open addressing':
            factor_list = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]
        else:
            factor_list = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        for load_factor in factor_list:
            times['test1'] = 0
            test1(load_factor=load_factor)
            mytimes[load_factor] = times['test1']
            mycounts[load_factor] = (1.0 * counts['compare']) / num_items

        mytimes = collections.OrderedDict(sorted(mytimes.items()))
        mycounts = collections.OrderedDict(sorted(mycounts.items()))
        plt.subplot('22' + str(iid))
        plt.plot(mycounts.keys(), mycounts.values(), color='red', marker='^', linewidth=2, alpha=0.3)
        plt.title('number of comparisons on ' + method + ' on book ' + book, fontsize=7)

        plt.subplot('22' + str(iid + 2))
        plt.plot(mytimes.keys(), mytimes.values(), color='blue', marker='o', linewidth=2, alpha=0.3)
        plt.title('time on ' + method + ' on book ' + book, fontsize=7)

    # plt.legend(prop={'size': 6})
    plt.tight_layout()
    plt.savefig('/Users/messi/Documents/ISE407/HW5/' + book + '.png', format='png', figsize=(6, 5), dpi=1000)
    plt.close()
