import csv

with open("data_analyze/data/paticipant.csv") as f:
    reader = csv.reader(f)
    lst = [row for row in reader]

with open("data_analyze/data/ID.txt", "r") as f:
    datalist = f.readlines()
    IDlist = [data for data in datalist]

with open("data_analyze/data/info_resque.txt", "w") as f:
    for row in lst:
        for i in IDlist:
            if i == row[0]:
                f.write(" ".join(row))
                
