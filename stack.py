"""Implementing a stack in Python, the super easy way then a hard way """

class StackFromList(object):

    def __init__(self):
        self.stack = []


    def push(self, element):
        self.stack.append(element)

    def pop(self):
        # Can also do
        # return self.stack.pop()
        temp = self.stack[-1]
        del self.stack[-1]
        return temp

    def top(self):
        # Easy way to implement:
        # return self.stack[-1]
        temp = self.pop()
        self.push(temp)
        return temp

    def isempty(self):
        return [] == self.stack




if __name__ == "__main__":
    stack1 = StackFromList()
    print "The stack is empty:", stack1.isempty()
    user_elements = raw_input("Please enter a stack: ")

    stack_these = user_elements.split()

    print "The stack is empty:", stack1.isempty()
    for item in stack_these:
        stack1.push(item)

    print "Done pushing."

    print "The top element is:", stack1.top()

    print "Now popping..."

    for index in xrange(len(stack1.stack)):
        print stack1.pop()
