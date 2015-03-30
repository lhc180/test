freeswitch.consoleLog("notice", "Debug from gen_dir_user_xml.lua, provide params:\n"..params:serialize().."\n")
local req_domain = params:getHeader("domain")
local req_key = params:getHeader("key")
local req_user = params:getHeader("user")

XML_STRING = 
[[<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<document type="freeswitch/xml">
	<section name="directory">
	<domain name="]]..req_domain..[[">
	<user id="]]..req_user..[[">
		<params>
			<params name="password" value="]]..req_user..[["/>
			<params name="vm-password" value="]]..req_user..[["/>
			<params name="dial-string" value="{sip_invite_domain=${dialed_domain},presence_id=$={dialed_user}@${dialed_domain}}${sofia_contact(${dialed_user}@${dialed_domain})}"/>
		</params>
		<variables>
		<variable name="toll_allow" value+"domestic, international,local"/>
		<param name="accountcode" value="]]..req_user..[["/>
		<variable name="user_context" value="default"/>
		<param name="effective_caller_id_number" value="]]..req_user..[["/>
		<param name="effective_caller_id_name" value="Extension]]..req_user..[["/>
		<variable name="outbound_caller_id_name" value="Extension 5678"/>
		<variable name="outbound_caller_id_number" value="5678"/>
		<variable name="callgroup" value="techsupport"/>
	</variables>
		</user>
	</domain>
	</section>
</document>]]
--commment the following line for production:
freeswitch.consoleLog("notice", "Debug from gen_dir_user_xml.lua, generated XML:\n"..XML_STRING.."\n")
