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

# methods = ['open addressing', 'chaining']
# books = ['goneWithTheWind', 'theCountOfMonteCristo']

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

        mytimes = {}
        mycounts = {}
        if method == 'open addressing':
            factor_list = [0.5]  # [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]
        else:
            factor_list = [5]  # [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        for load_factor in factor_list:
            dict_size = int(num_items / load_factor)
            word_count = Dict(dict_size)
            counts['compare'] = 0
            for word in words:
                if word not in word_count:
                    word_count[word] = 0
                word_count[word] += 1
            hash_value = []
            if method == 'open addressing':
                entry = word_count.table
                for i in range(len(entry)):
                    hash_value.append(entry[i].hash)
            else:
                for key in word_count.keys():
                    hash_value.append(word_count.hash(key))

            print('hash values', hash_value[:100])
            print('length of table', len(entry))
            print('length of hash_value', len(hash_value))

            plt.hist(hash_value, 50, range=(1, max(hash_value)), normed=True, facecolor='b', alpha=0.75)
            plt.xlabel('Hash value')
            plt.ylabel('Probability')
            plt.title('Histogram of hash values for ' + method)
            # plt.text(60, .025, r'$\mu=100,\ \sigma=15$')
            # plt.axis([40, 160, 0, 0.03])
            plt.grid(True)
            plt.tight_layout()
            plt.savefig('/Users/messi/Documents/ISE407/HW5/' + 'hist of hash value for ' + book + ' with ' + method + '.png', format='png', figsize=(10, 8), dpi=1000)
            plt.close()
