class OutCommon:
    def clean_data(self):
        # data = "some ./... ... \n"
        new_data = []
        for s in self.data:
            words = s.split(" ")
            while ("\n" in words):
                words.remove("\n")
            for i in range(len(words)):
                 if "\n" in words[i]:
                     words[i] = words[i][:-1]
            new_data.extend(words)
        self.data = new_data
            
    def read_from_file(self):
        with open(self.path, "r") as file:
            self.data = file.readlines()
    
    def __init__(self, path):
        self.path = path
        self.read_from_file()
        self.clean_data()


class OutLongest(OutCommon):
    def __init__(self, path):
        super().__init__(path)
        new_data = []
        root_and_childs = []
        for i in self.data:
            if i != "##":
                root_and_childs.append(i)
            else:
                new_data.append(root_and_childs)
                root_and_childs = []
        new_data.append(root_and_childs)
        self.data = new_data
    
    def __eq__(self, other):
        if not isinstance(other, OutCommon):
            return NotImplemented
        
        root_mark = (False, -1)
        for i in range(len(self.data)):
            if self.data[i][0] == other.data[0]:
                root_mark = True, i
                break
        if not root_mark[0]:
            return False
        for i in other.data[1:]:
            if not (i in self.data[root_mark[1]]):
                return False
        return True
        



class MostImportant(OutCommon):
    def __init__(self, path):
        super().__init__(path)
        if len(self.data) == 1:
            self.data = [self.data]
        else:
            new_data = []
            i = 0
            while i < len(self.data):
                new_data.append(
                    [self.data[i], self.data[i+1]]
                )
                i += 3
            self.data = new_data
        
    def __eq__(self, other):
        if isinstance(other, OutCommon):
            return other.data in self.data
        else:
            return NotImplemented