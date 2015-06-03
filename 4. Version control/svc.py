#how does this work?
#$python svc.py name_of_file.txt
#	...if the file is not present..an empty file of that name will be created
#$python svc.py N
#	...will check the present directory for Nth version...
#A log.txt file is created which contains number of versions created... 
#you have options to append ,delete and commit the changes you make to the main file as well as its versions

import os 
import sys

def commit(fname):
	with open(fname,'r',0) as f:
		data=f.read()
	with open("./log.txt",'r',0) as l:
		log=l.read()
	if not log :		
		print "\n log file empty.....creating version 0\n"		
		with open("./v_0.txt",'w',0) as v:
			v.write(data)
		with open("./log.txt",'w',0) as w:
			w.write("0\n")	
			
	else:			
		with open("./log.txt",'a+',0) as q:
			lines=q.readlines()
			i=str(int(lines[-1])+1)
			q.write(i+"\n")
		
		fname="./v_"+i+".txt"
		with open(fname,'w',0) as nv:
			nv.write(data)
		print "\n!!!! version "+i+" created!!!!\n"	
		view_version(fname)		

def view_version(fname):
	f=open(fname,'r',0)
	print "------------------contents of",fname,"are --------------------------\n"
	i=1
	for line in f.readlines():
		print i,line
		i+=1
		
	print "\n-----------------------------------------------------------------------"


def edit_version(fname):	
	e=0
	while e==0:		
		ch=int(raw_input("enter your choice \n1.append\n2.delete\n3.commit\n4.exit\n"))
		if ch==1:
			with open(fname,'r',0) as q:
				i=len(q.readlines())
			if i>=20:
				print "cant append...file full"
				
			else:
				aline=raw_input("enter line of max 10 characters to append \n")[:10]
				with open(fname,'a',0) as a:
					a.write(aline+"\n")
				view_version(fname)		
		elif ch==2 and open(fname,'r',0).read():	 		
			lno=(int(raw_input("enter the line number you want to remove\n ")))-1
			with open(fname,'r',0) as d:
				ll=d.readlines()
			while len(ll)<lno:
				print "line does not exist...enter again"
				lno=(int(raw_input("enter the line number you want to remove\n ")))-1
			del ll[lno]
			with open(fname,'w',0) as w:		
				w.writelines(ll)
			view_version(fname)
		
		elif ch==3:
			commit(fname)
		elif ch==4:
			e=1
		else:
			print "file is epmty ...cant delete"

if (os.path.isfile("./log.txt"))== False:
	os.system("touch ./log.txt")

if sys.argv[1].isdigit():
	print "looking for the version .........\n"
	fname="./v_"+sys.argv[1]+".txt"
	if sys.argv[1] in open("./log.txt").read():
		view_version(fname)
		edit_version(fname)
	else:
		print "version "+sys.argv[1]+" does not exist\n"
else:
	if (os.path.isfile("./"+sys.argv[1]))== False:
		print "no such file...creating new file..."
		os.system("touch ./"+sys.argv[1])
	fname=sys.argv[1]
	view_version(fname)
	edit_version(fname)
	





