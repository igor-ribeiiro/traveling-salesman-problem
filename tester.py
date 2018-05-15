import random
import os
import sys
import datetime

#Definitions
max_size = 5
only_max_size = False
number_of_tests = 99
max_float = 10
float_precision = 2

def program(name_1, name_2):
    os.system('mkdir ./test_samples')
    t3 = datetime.datetime.today()
    generate_samples('./')
    t1 = datetime.datetime.today()
    os.system('chmod +x ' + name_1 + ' && printf \'99\' | ./' + name_1)
    t1 = datetime.datetime.today() - t1
    os.system('mv ./saida.txt ./saida1.txt')
    t2 = datetime.datetime.today()
    os.system('chmod +x ' + name_2 + ' && printf \'99\' | ./' + name_2)
    t2 = datetime.datetime.today() - t2
    os.system('mv ./saida.txt ./saida2.txt')
    t3 = datetime.datetime.today() - t3

    f1 = open('saida1.txt', 'r')
    f2 = open('saida2.txt', 'r')

    lines_1 = f1.readlines()
    lines_2 = f2.readlines()

    all_passed = True
    result = ""

    for i in range(number_of_tests):
        msg = "#" + str(i+1) + ": " + lines_1[i].strip('\n') + " " + lines_2[i].strip('\n')
        if lines_1[i].strip('\n') == lines_2[i].strip('\n'):
            add = "Passed"
        else:
            add = "FAILED!"
            all_passed = False
        result += msg + ": " + add + '\n'

    if all_passed:
        result = ''

    print(result + "All passed: " + str(all_passed))
    t1 = str(t1.seconds) + "." + str(t1.microseconds)
    t2 = str(t2.seconds) + "." + str(t2.microseconds)
    print(name_1 + " took " + t1 + "s and " + name_2 + " took " + t2 + "s")

    os.system('mv ./ent* ./test_samples/')
    # os.system('rm -r ./test_samples')

def generate_samples(path):
    for i in range(number_of_tests):
        if not only_max_size:
            size = random.randint(0, max_size)
        else:
            size = max_size

        #Generating coordinates
        x_int = random.sample(range(1, max(random.randint(2, max_float*10**float_precision), size+1)), size)
        x_list = [x/10**float_precision for x in x_int]
        y_int = random.sample(range(1, max(random.randint(2, max_float*10**float_precision), size+1)), size)
        y_list = [y/10**float_precision for y in y_int]

        #Generating list
        l = [str(i+1) + " " + str(x_list[i]) + " " +str(y_list[i]) + '\n' for i in range(size)]
        random.shuffle(l)
        l = [str(size) + '\n'] + l
        w = open((path+"ent%02d.txt" % (i+1)), 'w')
        w.writelines(l)
        w.close()

if __name__ == "__main__":
    name_1 = sys.argv[1]
    name_2 = sys.argv[2]
    if len(sys.argv) > 3:
        max_size = int(sys.argv[3])
    program(name_1, name_2)
