import subprocess
import sys
import matplotlib.pyplot as plt
import pickle
import itertools

markers = itertools.cycle(('o', '+', '*'))

sizes = [1000, 5000, 10000, 20000, 40000, 60000, 100000]
versions = {'quick_sort': 0, 'merge_sort': 1}
results = {}

sys.path.append('Users/messi/Documents/ISE407/HW4/HW4_2/HW4_2')
for j in versions:
    results[j] = []
    for i in sizes:
        print('Using %s with size %d' % (j, i))
        c = subprocess.run(['/Users/messi/Documents/ISE407/HW4/HW4_2/HW4_2/all', '%d' % i, '%d' % versions[j]], stdout=subprocess.PIPE)
        # print(c.stdout.split()[11])
        results[j].append(float(c.stdout.split()[11]))
with open('results.dat', 'wb') as f:
    pickle.dump(results, f)
    pickle.dump(sizes, f)
    pickle.dump(versions, f)
# else:
#     with open('results.opt2.dat', 'rb') as f:
#         results = pickle.load(f)
#         sizes = pickle.load(f)
#         versions = pickle.load(f)
print(results)
for j in versions:
    plt.plot(sizes, results[j], marker=next(markers), label=j)
plt.legend()
plt.show()
