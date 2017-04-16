import json

f = open("./output.txt", "r")
lines = f.read()
lines = lines.split('\n')
lines = [(x.split()[1], x.split()[3]) for x in lines if len(x.split()) == 4]
f.close()

def getTree(pid, tree):
    temp_tree = dict()
    if not tree.has_key(pid):
        return dict()
    
    for process in tree[pid]:
        temp_tree[process] = getTree(process, tree)
    
    return temp_tree


tree = dict()
parent_id = lines[0][1]

pids = [x[1] for x in lines]
pids = set(pids)
pids = list(pids)
pids.sort()

for pid in pids:
    for line in lines:
        if line[0] == pid:
            if not tree.has_key(line[0]):
                tree[line[0]] = []
            tree[line[0]].append(line[1])

result = getTree(parent_id, tree)
result = {parent_id: result}
result = json.dumps(result, indent = 4)

f = open('./tree.json', 'w+')
f.write(result)
f.close()


