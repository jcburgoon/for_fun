#!/usr/bin/env python

# built-in module to parse XML; includes some xpath support
import xml.etree.ElementTree as ET

tree = ET.parse('/tmp/tools.nessus')

root = tree.getroot()

# get all report hosts -> needed to extract IP address
for host in root[1].findall('./ReportHost'):
    # get all report items and report plugins that are not Info
    for item in host.findall('./ReportItem'):
        if item.find('risk_factor').text != "None":
            print "Host IP: {}".format(host.attrib['name'])
            print "Plugin ID: {}".format(item.attrib['pluginID'])
            print "Plugin Name: {}".format(item.attrib['pluginName'])
            print "Severity: {}".format(item.find('risk_factor').text)
            print ""
