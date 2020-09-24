'''
function: find code with cpp extension with depth <= 2 
and build tex file for codebook
usage
1. du --max-depth=2 -a | grep "cpp" > list
2. python3 gen_codes.py > codes.tex
'''
with open("list", "r") as read_file:
    code_list = read_file.readlines()

cata = {}

for line in code_list:
    line = line[:-1]
    path, name = line.split("/")[1:]

    if not path in cata:
        cata[path] = []
    
    cata[path].append(name)


for topic in cata:
    print("\\section{{{}}}".format(topic))
    for algo in cata[topic]:
        print("\\subsection{{{}}}".format(algo[:-4].replace("_"," ")))
        print("\\lstinputlisting[language=C++]{{{}/{}}}".format(topic, algo))
    print()
