class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None


n = Node(1)
n.left = Node(2)
n.right = Node(3)
n.left.left = Node(4)
n.left.right = Node(5)
n.right.left = Node(6)
n.right.right = Node(7)


def DFS_Iterative(root):
    t = []
    stack = [root]
    while stack:
        node = stack.pop()
        if node is not None:
            t.append(node.val)
        if node.right is not None:
            stack.append(node.right)
        if node.left is not None:
            stack.append(node.left)
    return t


def DFS_Recursion(root):

    def helper(root, t):
        if root:
            t.append(root.val)
        if root.left:
            helper(root.left, t)
        if root.right:
            helper(root.right, t)
        return t

    return helper(root, [])


print(DFS_Iterative(n))
print(DFS_Recursion(n))