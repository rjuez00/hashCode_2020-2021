import math
import sys

class inputParser:
    def __init__(self, fileName):
        with open("input/" + fileName, "r") as file:
            lines = file.readlines()
        dataNodes = [int(node) for node in lines[0].split(" ")]
        self.data = {"seconds": dataNodes[0], "intersections": dataNodes[1], "streets": dataNodes[2], "cars": dataNodes[3], "bonus": dataNodes[4]}
        self.streetData = {}
        self.intersectionData = [None] * self.data['intersections']
        self.intersectionCount = 0
        
        for line in lines[1:self.data['streets'] + 1]:
            nodes = line.split(" ")
            self.streetData[nodes[2]] = {'startInter': int(nodes[0]), 'endInter': int(nodes[1]), 'time': int(nodes[3]), 'count': 0}
            if not self.intersectionData[int(nodes[1])]:
                self.intersectionData[int(nodes[1])] = []
                self.intersectionCount += 1

            self.intersectionData[int(nodes[1])].append(nodes[2])
            
        self.carData = []
        
        
        for line in lines[self.data['streets'] + 1:]:
            nodes = line.split()
            self.carData.append({'num': nodes[0], 'streets': nodes[1:]})
            for st in nodes[1:]:
                self.streetData[st]['count'] += 1

    def __str__(self):
        string = "Streets:\n"
        for key, elem in self.streetData.items():
            string += key + ": " + "Start Intersection: " + str(elem['startInter']) + ", End Intersection: " + str(elem['endInter']) + ", Time needed to traverse: " + str(elem['time']) + "\n"
        string += "Cars:\n"
        for elem in self.carData:
            string += "Number of streets to cross: " + str(elem['num']) + ", Path: " + str(elem['streets']) + "\n"
        return string
        
    
    
parse = inputParser(sys.argv[1])



n_intersecs = 0



for i in range(len(parse.intersectionData)):
    if(len(parse.intersectionData[i]) != 0):
        for calle in parse.intersectionData[i]:
            if parse.streetData[calle]['count'] != 0:
                n_intersecs += 1
                break


print(n_intersecs)


for i in range(len(parse.intersectionData)):
    if(len(parse.intersectionData[i]) != 0):
        streets_with_car = 0
        min_cars = math.inf
        for calle in parse.intersectionData[i]:
            if parse.streetData[calle]['count'] != 0:
                streets_with_car += 1
                if parse.streetData[calle]['count'] < min_cars:
                    min_cars = parse.streetData[calle]['count']
        if streets_with_car != 0:
            print(i)
            print(streets_with_car)
            for calle in parse.intersectionData[i]:
                if parse.streetData[calle]['count'] != 0:
                    print(calle, math.floor(parse.streetData[calle]['count']/min_cars))



