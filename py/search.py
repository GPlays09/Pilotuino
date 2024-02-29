import os, sys

def look(path, phrase):
    for p in os.listdir(path):
        if os.path.isfile(path+p):
            if not(p.split('.')[-1] in ['cpp', 'h', 'c']):
                continue

            try:
                f = open(path+p, 'r', encoding='utf-8')
                d = f.read()
                f.close()
            except UnicodeDecodeError:
                print("ERROR:", path+p)
                continue

            if phrase in d:
                print(path+p)
                pass
        else:
            look(path+p+'\\', phrase)

look("..\\hardware\\", sys.argv[1])