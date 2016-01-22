function ipverify(ip_string){
	var c;
	var n = 0;
	var ch = ".0123456789";
	if (ip_string.length < 7 || ip_string.length > 15)
		return false;
	for (var i = 0; i < ip_string.length; i++){
		c = ip_string.charAt(i);
		if (ch.indexOf(c) == -1)
			return false;
		else{
			if (c == '.'){
				if(ip_string.charAt(i+1) != '.')
					n++;
				else
					return false;
			}		
		}
	}
	if (n != 3)
		return false;
	if (ip_string.indexOf('.') == 0 || ip_string.lastIndexOf('.') == (ip_string.length - 1))
		return false; 
		
	szarray = [0,0,0,0];
	var remain;
	var i;
	for(i = 0; i < 3; i++){
		var n = ip_string.indexOf('.');
		szarray[i] = ip_string.substring(0,n);
		remain = ip_string.substring(n+1);
		ip_string = remain;
	}
	szarray[3] = remain;
	for(i = 0; i < 4; i++){
		if (szarray[i] < 0 || szarray[i] > 255){
			return false;
		}
	}		
	return true;	
}
function is_ipaddr(ip_string){
	if(ip_string.length == 0){
		alert("请输入IP地址！");
		return false;
	}
	if (!ipverify(ip_string)){
		alert("IP地址输入错误，请重新输入！");
		return false;
	}	
	return true;
}
function is_maskaddr(mask_string){
	if(mask_string.length == 0){
		alert("请输入子网掩码（例如255.255.255.0）！");
		return false;
	}
	if (!ipverify(mask_string)){
		alert("子网掩码输入错误，请重新输入（例如255.255.255.0）！");
		return false;
	}	
	return true;
}
function is_gatewayaddr(gateway_string){
	if(gateway_string.length == 0){
		alert("请输入网关！");
		return false;
	}
	if (!ipverify(gateway_string)){
		alert("网关输入错误，请重新输入！");
		return false;
	}	
	return true;
}
function is_dnsaddr(dns_string){
	if(dns_string.length == 0){
		alert("请输入DNS服务器（例如202.96.134.133）！");
		return false;
	}
	if (!ipverify(dns_string)){
		alert("DNS服务器输入错误，请重新输入（例如202.96.134.133）！");
		return false;
	}	
	return true;
}
function macverify(mac_string){
	var c;
	var n = 0;
	var ch = "-0123456789ABCDEFabcdef";
	if (mac_string.length != 17)
			return false;
	for (var i = 0; i < mac_string.length; i++){
		c = mac_string.charAt(i);
		if (ch.indexOf(c) == -1)
			return false;
		else{
			if (c == '-')
				n++;		
		}
	}
	if (n != 5)
			return false;
	for(var i = 2; i < 17; i += 3){
		if (mac_string.charAt(i) != '-')
			return false;
	}
	return true;	
}
function is_macaddr(mac_string){
	if(mac_string.length == 0){
		alert("请输入MAC地址！");
		return false;
	}
	if (!macverify(mac_string)){
		alert("MAC地址输入错误，请重新输入！");
		return false;
	}
	return true;	
}
function is_number(num_string,nMin,nMax){
	var c;
	var ch = "0123456789";
	for (var i = 0; i < num_string.length; i++){
		c = num_string.charAt(i);
		if (ch.indexOf(c) == -1)
			return false;
	}
	if(parseInt(num_string) < nMin || parseInt(num_string) > nMax)
		return false;
	return true;
}
function charCompare(szname,en_limit,cn_limit){
	var c;
	var ch = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_.><,[]{}?/+=|\\'\":;~!#$%()` & ";
	if(szname.length > en_limit)
		return false;
	for (var i = 0; i < szname.length; i++){
		c = szname.charAt(i);
		if (ch.indexOf(c) == -1){
			if(szname.length > cn_limit)
				return false;
		}
	}
	return true;
}		
function is_hostname(name_string){
	var EN_LIMIT = 30;	
	var CN_LIMIT = 15;
	if(!charCompare(name_string,EN_LIMIT,CN_LIMIT)){
		alert("您最多只能输入15个中文或30个英文字符，请重新输入！");
		return false;
	}
	else
		return true;
}	