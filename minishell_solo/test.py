class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

def reverse_linked_list(head):
    prev = None
    current = head
    
    while current:
        next_node = current.next
        current.next = prev
        prev = current
        current = next_node
    
    return prev  # prev is the new head

# Example usage:
# Create a simple linked list 1 -> 2 -> 3 -> None
head = Node(1)
head.next = Node(2)
head.next.next = Node(3)
head.next.next.next = Node(4)
head.next.next.next.next = Node(5)
head.next.next.next.next.next = Node(6)
head.next.next.next.next.next.next = Node(7)

current = head
while current:
    print(current.data, end=" -> ")
    current = current.next
print("")

# Reverse the list
reversed_head = reverse_linked_list(head)

# Print reversed list (3 -> 2 -> 1 -> None)
current = reversed_head
while current:
    print(current.data, end=" -> ")
    current = current.next
print("")
