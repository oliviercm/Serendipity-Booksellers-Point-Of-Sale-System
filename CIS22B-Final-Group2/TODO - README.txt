----------------------------
ORDERED IN GENERAL PRIORITY
----------------------------


checkout doesnt clear the cart properly, even after checking out there are ghost books left behind, which can be seen by going to checkout again
	>>upon further study it seems as though removeBookFromCart is flawed and doesnt fully remove the book,
			not only that but it doesnt set every attribute to 0 or empty, instead it only sets isbn, title, and retail


cashier cart: adding two of the same book then removing that book from cart twice displays an error for the second book
	even though the book really does get removed in a way - there is a ghost book in checkout screen
	>>upon further study it seems as though removeBookFromCart is flawed and doesnt fully remove the book,
		not only that but it doesnt set every attribute to 0 or empty, instead it only sets isbn, title, and retail

		
reciept: bars arent long enough/dont line up properly, needs to display subtotal, tax, total
		
cashier: adding and removing books from the cart actually edits the real inventory even though it shouldn't do this
	until checkout
	
	
cashier: printing out the reciept doesnt properly line up the book info with the columns


cashier: the only time the inventory array is gotten is during construction - this is dangerous since
	this is only a copy of the array.
	fix would be instead of storing the inventoryarray pointer, store the inventorydatabase pointer.
	then, whenever there is a need for the array, use the pointer to grab a new copy of the array
	>>not sure whether this is affecting how to code works or not, could this be the cause of the other bugs?
		if it is, then this is top priority
		
		
inventory add books: checking to see whether a string is an isbn by using stoi exception checking is inelegant and actually allows the user to put in
	an invalid isbn if there are characters only on the beginning or end of the string
	>>main problem is the limitations of the project, it is possible to solve this using regex
		but that might not be allowed for this project. is there an elegant solution within our limitations?

		
inventory add books: checking whether date is valid doesnt check if the day/month is logical ie. 87/53/2019


display: having all these repeated couts for every time we print out options is getting very cluttered with all the repetition,
	the non-lazy way to fix this would be to write a function that takes a few needed parameters and prints out the screen
	>>this goes the same for the headers in the reports that go (TITLE: AUTHOR: PUBLISHER:, etc.), writing a
		function that takes care of that instead of doing a hardcoded thing would be much more elegant