__author__ = 'JohnHook'

class Tree:
    def __init__(self, leaf=False, value='', weight=0, left=0, right=0):
        self.left, self.right = left, right
        self.leaf, self.value, self.weight = leaf, value, weight

    def __lt__(self, other):
        return self.weight < other.weight

class Archive:
    def __init__(self, file_name):
        stat = {}
        file = open(file_name, mode='rb')
        for _ch in file.read():
            ch = chr(_ch)
            if ch in stat.keys():
                stat[ch] += 1
            else:
                stat[ch] = 1
        file.close()

        from heapq import heappush as push, heappop as pop
        forest = []
        for ch in sorted(stat.keys()):
            push(forest, Tree(True, ch, stat[ch]))

        while len(forest) >= 2:
            left = pop(forest)
            right = pop(forest)
            push(forest, Tree(left=left, right=right, weight=(left.weight + right.weight)))

        self.t = pop(forest)
        base = {}

        def rec(t, tmp):
            if t.leaf == True:
                base[t.value] = tmp
            else:
                rec(t.left, tmp + '0')
                rec(t.right, tmp + '1')
        rec(self.t, '')

        self.a = ''
        buffer = ''
        file = open(file_name, mode='rb')
        for _ch in file.read():
            ch = chr(_ch)
            for b in base[ch]:
                if len(buffer) == 8:
                    tmp = 0
                    for i in range(8):
                        tmp *= 2
                        if buffer[i] == '1':
                            tmp += 1
                    self.a += chr(tmp)
                    buffer = ''
                buffer += b
        self.tail = buffer
        file.close()


    def un(self, file_name):
        def get():
            for ch in self.a:
                tmp = ord(ch)
                buffer = ''
                for i in range(8):
                    buffer += '1' if tmp % 2 == 1 else '0'
                    tmp //= 2
                for i in reversed(buffer):
                    yield int(i == '1')
            for ch in self.tail:
                yield int(ch == '1')

        act = self.t
        file = open(file_name, mode='w')
        for tmp in get():
            act = act.left if tmp == 0 else act.right

            if act.leaf == True:
                file.write(act.value)
                act = self.t

        file.close()

from argparse import ArgumentParser

def parse_args():
    parser = ArgumentParser(description="---")

    parser.add_argument('-a', '--archive', help="---", action='store_true')
    parser.add_argument('-u', '--unarchive', help="---", action='store_true')
    parser.add_argument('file_name')

    return vars(parser.parse_args())


def get_arguments():
    args = parse_args()
    fn = args['file_name']

    import pickle
    if args['archive']:
        data = Archive(fn)
        with open(fn + '.jh', 'wb') as f:
            pickle.dump(data, f)

    if args['unarchive']:
        with open(fn + '.jh', 'rb') as f:
            data = pickle.load(f)
        data.un(fn)

if __name__ == "__main__":
    get_arguments()

