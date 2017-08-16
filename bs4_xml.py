#!/usr/bin/env python

# for this to work, you need to install bs4 and lxml
from bs4 import BeautifulSoup

with open('/tmp/tools.nessus') as report:
    soup = BeautifulSoup(report, 'lxml')

# simpler to implement making it easier to make the code more efficient
# but ElementTree is a lot faster
# bs4 3.250s
# vs
# et  0.760s
for item in soup.find_all('reportitem'):
    if item.risk_factor.text != 'None':
        print "Host IP: {}".format(item.parent['name'])
        print "Plugin ID: {}".format(item['pluginid'])
        print "Plugin Name: {}".format(item['pluginname'])
        print "Severity: {}".format(item.risk_factor.text)
        print ""