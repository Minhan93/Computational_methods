import subprocess
import sys
import matplotlib.pyplot as plt
import pickle
import itertools

markers = itertools.cycle(('o', '+', '*'))

sizes = [8, 16, 32, 64, 128, 256, 512]
threads = [1, 3, 7, 10, 12, 14]
versions = {'sequential': 1, 'parallel': 2}
results = {}

sys.path.append('/home/mil417/ISE407/HW4/HW4_1/HW4_1')
for j in versions:

    if versions[j] == 1:
        results[j] = []
        f0 = open(j + '.txt', 'w')
        for i in sizes:
            c = subprocess.run(['/home/mil417/ISE407/HW4/HW4_1/HW4_1/main1', '%d' % i], stdout=subprocess.PIPE)
            print(float(c.stdout.split()[5]))
            results[j].append(float(c.stdout.split()[5]))
            f0.write('%f\n' % float(c.stdout.split()[5]))
        f0.close()
    else:
        for k in threads:
            results[j + str(k)] = []
            f0 = open(j + '_thread' + str(k) + '.txt', 'w')
            for i in sizes:
                print('Using %s with size %d with thread %d' % (j, i, k))

                c = subprocess.run(['/home/mil417/ISE407/HW4/HW4_1/HW4_1/main2', '%d' % i, '%d' % k], stdout=subprocess.PIPE)
            # print(c.stdout.split()[11])
                print(float(c.stdout.split()[5]))
                results[j + str(k)].append(float(c.stdout.split()[5]))
                f0.write('%f\n' % float(c.stdout.split()[5]))
            f0.close()

with open('results.dat', 'wb') as f:
    pickle.dump(results, f)
    pickle.dump(sizes, f)
    pickle.dump(versions, f)
    pickle.dump(threads, f)
# else:
#     with open('results.opt2.dat', 'rb') as f:
#         results = pickle.load(f)
#         sizes = pickle.load(f)
#         versions = pickle.load(f)

# print(results)
# for j in versions:
#     plt.plot(sizes, results[j], marker=next(markers), label=j)
# plt.legend()
# plt.show()
