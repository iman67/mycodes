#-*- coding: utf-8 -*-
from bs4 import BeautifulSoup
from urllib2 import urlopen
import requests
requests.packages.urllib3.disable_warnings()

import ssl

try:
    _create_unverified_https_context = ssl._create_unverified_context
except AttributeError:
    # Legacy Python that doesn't verify HTTPS certificates by default
    pass
else:
    # Handle target environment that doesn't support HTTPS verification
    ssl._create_default_https_context = _create_unverified_https_context
# if has Chinese, apply decode()
html = urlopen("https://www.arzlive.com/").read().decode('utf-8')

soup = BeautifulSoup(html, features='lxml')
#<td class="s3_10 price">28,510,000</td>
htmla = urlopen("https://www.iranjib.ir/showgroup/23/realtime_price/").read().decode('utf-8')

soupa = BeautifulSoup(htmla, features='lxml')
# print with title
for item in soup.find("td", {"class": "s3_11 price"}): 
    int_b = int(item.replace(',',''))
for item2 in soup.find("td", {"class": "s3_12 price"}):
    int_b2 = int(item2.replace(',',''))
for item3 in soup.find("td", {"class": "s3_13 price"}):
    int_b3 = int(item3.replace(',',''))
for item4 in soupa.find("td",{"id":"f_105_68_pr"}).find("span",{"class":"lastprice"}):
    
    int_b5 = int(item4.replace(',',''))
    #print int_b5
    a = int(int_b) 
    b = int(int_b2)
    c = int(int_b3)
    d = int(int_b5)
    x = d*10
    print (a)
    print (b)
    print (c)
    print (x)
    #a = int(raw_input("Price of nim = "))
    #b = int(raw_input("price of rob = "))
    #c = int(raw_input("price of euro= "))
    d = (b - 12550000)*20
    e = (b - 13650000)*8
    f = (b - 13550000)*11
    #g = d + e + f 
    h = (c - 7050000)*12
    j = (b - 19000000) #one coin gold
    #i = (b-9500)*2000 
    g = d + e + f + h + j
   # sodeuro=
    print ('sodSeke='),g
    z=3000*x
    t=(b*41)+(15*c)+(a)
    t2=(b*41)+(15*c)+(a)+(z)
    print ('total Seke='),t
    print ('totalwitheuro='),t2
    print ('euro='),z
    #k = (b*40) + (b*15) + (b*3000) + 7000000  
    #print k
#htmla = urlopen("https://www.iranjib.ir/showgroup/23/realtime_price/").read().decode('utf-8')

#soupa = BeautifulSoup(htmla, features='lxml')
#for item in soupa.find("td",{"id":"f_105_68_pr"}).find("span",{"class":"lastprice"}):
#    int_b5 = int(item4.replace(',',''))
#    print int_b5 
#print("-------------------------")
# print without title
#for item in soup.find("table", {"id": "course-list"}).tr.next_siblings:
 #   print(item)

#print("-------------------------")
# navigate using next_sibling/previous_sibling
#print(soup.find("img", {"src": "https://morvanzhou.github.io/static/img/course_cover/scraping.jpg"}
#                ).parent.previous_sibling.get_text())
