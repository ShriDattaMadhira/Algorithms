import math


class Node:
    def __init__(self, datakey=None, dataval=None):
        self.datakey = datakey
        self.dataval = dataval
        self.nextval = None


class SLL:
    def __init__(self):
        self.headval = None

    def insert_at_start(self, newkey, newval):
        NewNode = Node(newkey, newval)
        NewNode.nextval = self.headval
        self.headval = NewNode

    def delete(self, Removekey):
        HeadVal = self.headval
        if HeadVal is not None:
            if HeadVal.datakey == Removekey:
                self.headval = HeadVal.nextval
                HeadVal = None
                return
        while HeadVal is not None:
            if HeadVal.datakey == Removekey:
                break
            prev = HeadVal
            HeadVal = HeadVal.nextval
        if HeadVal is None:
            return
        prev.nextval = HeadVal.nextval
        HeadVal = None

    def print(self, index):
        printval = self.headval
        if printval is None:
            print("hashTable ---> None")  # index,
            return
        print("hashTable", end=" ")  # index
        while printval is not None:
            print("-->", end=" ")
            print("[", printval.datakey, ", ", printval.dataval, "]", end=" ")
            printval = printval.nextval
        print()

    def search(self, key):
        is_there = 0
        temp_head = self.headval
        while temp_head is not None:
            if temp_head.datakey == key:
                is_there = 1
                break
            else:
                temp_head = temp_head.nextval
        if is_there == 1:
            return temp_head
        else:
            return -1


def display_hash(hashTable):
    for j in range(len(hashTable)):
        hashTable[j].print(j)


# Hashing Function to return key for every value.
def Hashing(key):
    hash_val = 5381
    asc = 0
    ord_list = [ord(c) for c in key]
    ord_list.reverse()
    for i in range(len(ord_list)):
        asc += (ord_list[i] * (128 ** i)) % (len(HashTable))
    return (((hash_val << 5) + hash_val) + asc) % (len(HashTable))


# Insert Function to add values to the hash table
def insert(Hashtable, head, hash_val, key, value):
    head.insert_at_start(key, value)
    Hashtable[hash_val] = head


f = open("./aliceinwonderland", 'r')
lines = f.read()
f.close()
length = len(lines.split())

# Creating Hashtable
HashTable = []
for index in range(math.ceil(length / 5)):
    HashTable.append(SLL())

for i in lines.split():
    flag = 0
    hash_value = Hashing(i.lower())
    hashes_head = HashTable[hash_value]
    if hashes_head.headval is None:
        insert(HashTable, hashes_head, hash_value, i.lower(), 1)
    else:
        flag = hashes_head.search(i.lower())
        if flag == -1:
            insert(HashTable, hashes_head, hash_value, i.lower(), 1)
        else:
            flag.dataval += 1

ch = True
while ch:
    print("1. Insert 2. Delete 3. Print all keys 4. Search 0. Exit")
    option = int(input("Enter any option: "))
    if option == 1:
        word = str(input("Enter the word you want to Insert: "))
        hash_value = Hashing(word.lower())
        head = HashTable[hash_value]
        flag = head.search(word.lower())
        if flag == -1:
            insert(HashTable, head, hash_value, word.lower(), 1)
        else:
            flag.dataval += 1
    elif option == 2:
        word = str(input("Enter the word you want to Delete: "))
        hash_value = Hashing(word.lower())
        head = HashTable[hash_value]
        head.delete(word.lower())
    elif option == 3:
        display_hash(HashTable)
    elif option == 4:
        word = str(input("Enter the word you want to Search: "))
        hash_value = Hashing(word.lower())
        head = HashTable[hash_value]
        flag = head.search(word.lower())
        if flag == -1:
            print(word, ": KEY NOT FOUND")
        else:
            print("KEY:", flag.datakey)
            print("WORD COUNT:", flag.dataval)
    elif option == 0:
        ch = False
    else:
        print("Enter a valid option.")
