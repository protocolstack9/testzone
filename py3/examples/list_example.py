#create a list with a few sample items
myList = [1,2,3,4,5]
 
#len() gives a count of how many items our list holds
print("myList has ", len(myList), " items.")
 
#The items in a list don't have to be of the same type
myList.append("six")
myList.append("seven")
myList.append(8)
 
#We've appended three new items to the end of the list
print("myList now has",len(myList), " items.")
 
#Now let's see item number 0 (first item)
print("first item:", myList[0])
 
#and now the fourth item
print("fourth item:", myList[3])
 
#Then pop the last item out of the list
print("and ends with" , myList.pop())
print("myList now has",len(myList), " items.")
 
#And see what we've done
print("The complete contents are:", myList)


myStr = "Hello, world!"
print(myStr, "len: ", len(myStr))
