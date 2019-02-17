import csv

BASE_PATH = "data/"

class Query:
    def __init__(self,name):
        self.gen = load_csv(name)

    def eq(self,k,v):
        self.gen = (row for row in self.gen if row[k] == v)
        return self

    def ins(self,k,vs):
        self.gen = (row for row in self.gen if row[k] in vs)
        return self

    def select(self,ks):
        self.gen = ({k:v for k,v in row.items() if k in set(ks)} for row in self.gen)
        return self

    def get(self,k):
        self.gen = (row[k] for row in self.gen)
        return self

    def join(self,table,k):
        idx = Query(table).index(k)
        self.gen = (dict(idx[row[k]], **row) for row in self.gen)
        return self

    def distinct(self):
        self.gen = dedupe(self.gen)
        return self

    def index(self,k):
        table = {}
        for row in self.gen:
            table[row[k]] = row
    
        return table

    def as_set(self):
        return {row for row in self.gen}
    
    def as_gen(self):
        return self.gen
    
   

def load_csv(name):
        with open(BASE_PATH + name + '.txt') as f:
            reader =  csv.DictReader(f)
            for row in reader:
                yield row

def dedupe(gen):
        seen = set([])
        for row in gen:
            if row not in seen:
                seen.add(row)
                yield row
