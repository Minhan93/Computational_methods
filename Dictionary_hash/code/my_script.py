import re
import csv
import numpy as np
import math
import scipy.io as sio
import os
import timeit
import matplotlib
import matplotlib.pyplot as plt
from sys import argv, exit, stdout
from numpy import linalg as la
from dictionary_oa import *
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--file', help='filename')
parser.add_argument('--word', help='the key to search')
parser.add_argument('--sort', help='sort by values', type=int)
args = parser.parse_args()
# print args.file
# print args.word
# print args.sort

# load text
filename = '/Users/messi/Documents/ISE407/HW5/' + args.file
file = open(filename, 'rt')
text = file.read()
file.close()
# split based on words only
words = re.sub(r'[0-9]+', '', text)
words = re.split(r'\W+', words)

num = len(words)
word_count = Dict(num)
for word in words:
    if word not in word_count:
        word_count[word] = 0
    word_count[word] += 1

if args.word is not None:
    print 'the word %s occured %d times' % (args.word, word_count[args.word])

if args.sort is not None:
    for key, value in sorted(word_count.iteritems(), key=lambda (k, v): (v, k))[-args.sort:]:
        print "%s: %s" % (key, value)
