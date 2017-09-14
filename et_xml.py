#!/usr/bin/env python

# built-in module to parse XML; includes some xpath support
import xml.etree.ElementTree as ET

tree = ET.parse('/root/tools.nessus')

root = tree.getroot()

for host in root[1].findall('./ReportHost'):
    for item in host.findall('./ReportItem'):
        if item.find('risk_factor').text != "None":
            print("Host IP: {}".format(host.get('name')))
            print("Plugin ID: {}".format(item.get('pluginID')))
            print("Plugin Name: {}".format(item.get('pluginName')))
            print("Severity: {}".format(item.find('risk_factor').text))
            print("")
