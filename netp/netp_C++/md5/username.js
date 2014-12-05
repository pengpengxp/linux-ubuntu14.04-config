/////////////////////////////////////
//代码原作者博客:http://www.box6.cn
//修改人zsl1005
//本人只是从官方客户端反编译了一个重庆使用的参数,为了能够运行，略微修改了下代码
//md5代码来源于MD5官方技术站点
//获取Timec
//子函数/////////////////////////////
function getTimec()
{
								//获取时间的值
								var zeroDate = new Date(0);
								var nowDate = new Date();
								nowDate-=nowDate.getMilliseconds();
								zeroDate/=1000;
								nowDate/=1000;
								var tDate = nowDate - zeroDate;
								//时间初处理Timec为结果
								var Timec = tDate;
								Timec *= 1717986919;
								Timec /= 4294967296;
								Timec=Math.floor(Timec);
								Timec /= 2;
								Timec=Math.floor(Timec);
								return Timec;
}
/////////////////////////////////////
//星空用户名获取主函数
//主函数/////////////////////////////
function xkv18(username)
{
								//var         RADIUS = "chongqingradius1";
								var RADIUS = "cqxinliradius002";
								var                LR = "\r\n";
								/////////////////////////////////////
								//获取md5加密参数的第一部分
								timec = getTimec()
																var S = new Array(4); 
								var t = timec;
								S[3] = (t & 0xFF);
								S[2] = (t & 0xFF00) / 0x100  ;
								S[1] = (t & 0xFF0000) / 0x10000;
								S[0] = (t & 0xFF000000) / 0x1000000;
								print(S[3]);
								print(S[2]);
								print(S[1]);
								print(S[0]);
								var s1md5=new String("");
								for(var i=0;i<4;i++)
								{
																s1md5+=String.fromCharCode(S[i]);
								}

								/////////////////////////////////////
								//倒置过程lTime1Converted为结果
								var S2 = new Array(4); 
								S2[3] = S[0];
								S2[2] = S[1];
								S2[1] = S[2];
								S2[0] = S[3];
/*
for(var w=0;w<4;w++)
{
	print("S2=");
	print(S2[w]);
}
*/
								/////////////////////////////////////
								var S3 = new Array(4);
								S3[0]=0;
								S3[1]=0;
								S3[2]=0;
								S3[3]=0;
								var        i = 0, j = 0, k = 0;
								for (i = 0; i < 0x20; i++)
								{
																j = Math.floor(i / 0x8);
																k = 3 - (i % 0x4);

																S3[k] *= 0x2;

																if (Math.floor(S2[j] % 2) == 1)
																{
																								S3[k]++;

																}
																S2[j] /= 2;
																S2[j]=(Math.floor(S2[j]));
}
/*
for(var w=0;w<4;w++)
{
	print("S3=");
	print(S3[w]);
}
*/
								//////////////////////////////////////
								var S4 = new Array(6);
								S4[0]=0;
								S4[1]=0;
								S4[2]=0;
								S4[3]=0;
								S4[4]=0;
								S4[5]=0;
								var t1, t2;
								t1 = S3[3];
								t1 /= 0x4;
								S4[0] = Math.floor(t1);
								t1 = S3[3];
								t1 = t1 & 0x3;
								t1 *= 0x10;
								S4[1] = Math.floor(t1);
								t2 = S3[2];
								t2 /= 0x10;
								t2 = t2 | t1;
								S4[1] = Math.floor(t2);
								t1 = S3[2];
								t1 = t1 & 0x0F;
								t1 *= 0x04;
								S4[2] = Math.floor(t1);
								t2 = S3[1];
								t2 /= 0x40;
								t2 = t2 | t1;
								S4[2] = Math.floor(t2);
								t1 = S3[1];
								t1 = t1 & 0x3F;
								S4[3] = Math.floor(t1);
								t2 = S3[0];
								t2 /= 0x04;
								S4[4] = Math.floor(t2);
								t1 = S3[0];
								t1 = t1 & 0x03;
								t1 *= 0x10;
								S4[5] = Math.floor(t1);
								//////////
for (i = 0; i < 6; i++)
{
S4[i] += 0x20;
	if ((S4[i]) >= 0x40)
	{
	S4[i]++;
	}
}
	print("S4=");
for(var w=0;w<6;w++)
{
	print(S4[w]);
}

								////////////////////////////////////
								var sFormatString=new String("");
								for(var i=0;i<6;i++)
								{
																sFormatString+=String.fromCharCode(S4[i]);
								}
								var strInput = s1md5 + username.substr(0, username.indexOf('@')) + RADIUS;
								print(strInput);
								var sMd5 = hex_md5(strInput);
								print(sMd5);
								var sMD5Used = sMd5.substr(0, 2);
								print(sFormatString);
								var sRealUsername = LR + sFormatString + sMD5Used + username;
								print(sRealUsername)
																return sRealUsername;
}

/*
	* A JavaScript implementation of the RSA Data Security, Inc. MD5 Message
	* Digest Algorithm, as defined in RFC 1321.
	* Version 2.1 Copyright (C) Paul Johnston 1999 - 2002.
	* Other contributors: Greg Holt, Andrew Kepert, Ydnar, Lostinet
	* Distributed under the BSD License
	* See http://pajhome.org.uk/crypt/md5 for more info.
	*/

/*
	* Configurable variables. You may need to tweak these to be compatible with
	* the server-side, but the defaults work in most cases.
	*/
var hexcase = 0;  /* hex output format. 0 - lowercase; 1 - uppercase        */
var b64pad  = ""; /* base-64 pad character. "=" for strict RFC compliance   */
var chrsz   = 8;  /* bits per input character. 8 - ASCII; 16 - Unicode      */

/*
	* These are the functions you'll usually want to call
	* They take string arguments and return either hex or base-64 encoded strings
	*/
function hex_md5(s){ return binl2hex(core_md5(str2binl(s), s.length * chrsz));}
function b64_md5(s){ return binl2b64(core_md5(str2binl(s), s.length * chrsz));}
function str_md5(s){ return binl2str(core_md5(str2binl(s), s.length * chrsz));}
function hex_hmac_md5(key, data) { return binl2hex(core_hmac_md5(key, data)); }
function b64_hmac_md5(key, data) { return binl2b64(core_hmac_md5(key, data)); }
function str_hmac_md5(key, data) { return binl2str(core_hmac_md5(key, data)); }

/*
	* Perform a simple self-test to see if the VM is working
	*/
function md5_vm_test()
{
								return hex_md5("abc") == "900150983cd24fb0d6963f7d28e17f72";
}

/*
	* Calculate the MD5 of an array of little-endian words, and a bit length
	*/
function core_md5(x, len)
{
								/* append padding */
								x[len >> 5] |= 0x80 << ((len) % 32);
								x[(((len + 64) >>> 9) << 4) + 14] = len;

								var a =  1732584193;
								var b = -271733879;
								var c = -1732584194;
								var d =  271733878;

								for(var i = 0; i < x.length; i += 16)
								{
																var olda = a;
																var oldb = b;
																var oldc = c;
																var oldd = d;

																a = md5_ff(a, b, c, d, x[i+ 0], 7 , -680876936);
																d = md5_ff(d, a, b, c, x[i+ 1], 12, -389564586);
																c = md5_ff(c, d, a, b, x[i+ 2], 17,  606105819);
																b = md5_ff(b, c, d, a, x[i+ 3], 22, -1044525330);
																a = md5_ff(a, b, c, d, x[i+ 4], 7 , -176418897);
																d = md5_ff(d, a, b, c, x[i+ 5], 12,  1200080426);
																c = md5_ff(c, d, a, b, x[i+ 6], 17, -1473231341);
																b = md5_ff(b, c, d, a, x[i+ 7], 22, -45705983);
																a = md5_ff(a, b, c, d, x[i+ 8], 7 ,  1770035416);
																d = md5_ff(d, a, b, c, x[i+ 9], 12, -1958414417);
																c = md5_ff(c, d, a, b, x[i+10], 17, -42063);
																b = md5_ff(b, c, d, a, x[i+11], 22, -1990404162);
																a = md5_ff(a, b, c, d, x[i+12], 7 ,  1804603682);
																d = md5_ff(d, a, b, c, x[i+13], 12, -40341101);
																c = md5_ff(c, d, a, b, x[i+14], 17, -1502002290);
																b = md5_ff(b, c, d, a, x[i+15], 22,  1236535329);

																a = md5_gg(a, b, c, d, x[i+ 1], 5 , -165796510);
																d = md5_gg(d, a, b, c, x[i+ 6], 9 , -1069501632);
																c = md5_gg(c, d, a, b, x[i+11], 14,  643717713);
																b = md5_gg(b, c, d, a, x[i+ 0], 20, -373897302);
																a = md5_gg(a, b, c, d, x[i+ 5], 5 , -701558691);
																d = md5_gg(d, a, b, c, x[i+10], 9 ,  38016083);
																c = md5_gg(c, d, a, b, x[i+15], 14, -660478335);
																b = md5_gg(b, c, d, a, x[i+ 4], 20, -405537848);
																a = md5_gg(a, b, c, d, x[i+ 9], 5 ,  568446438);
																d = md5_gg(d, a, b, c, x[i+14], 9 , -1019803690);
																c = md5_gg(c, d, a, b, x[i+ 3], 14, -187363961);
																b = md5_gg(b, c, d, a, x[i+ 8], 20,  1163531501);
																a = md5_gg(a, b, c, d, x[i+13], 5 , -1444681467);
																d = md5_gg(d, a, b, c, x[i+ 2], 9 , -51403784);
																c = md5_gg(c, d, a, b, x[i+ 7], 14,  1735328473);
																b = md5_gg(b, c, d, a, x[i+12], 20, -1926607734);

																a = md5_hh(a, b, c, d, x[i+ 5], 4 , -378558);
																d = md5_hh(d, a, b, c, x[i+ 8], 11, -2022574463);
																c = md5_hh(c, d, a, b, x[i+11], 16,  1839030562);
																b = md5_hh(b, c, d, a, x[i+14], 23, -35309556);
																a = md5_hh(a, b, c, d, x[i+ 1], 4 , -1530992060);
																d = md5_hh(d, a, b, c, x[i+ 4], 11,  1272893353);
																c = md5_hh(c, d, a, b, x[i+ 7], 16, -155497632);
																b = md5_hh(b, c, d, a, x[i+10], 23, -1094730640);
																a = md5_hh(a, b, c, d, x[i+13], 4 ,  681279174);
																d = md5_hh(d, a, b, c, x[i+ 0], 11, -358537222);
																c = md5_hh(c, d, a, b, x[i+ 3], 16, -722521979);
																b = md5_hh(b, c, d, a, x[i+ 6], 23,  76029189);
																a = md5_hh(a, b, c, d, x[i+ 9], 4 , -640364487);
																d = md5_hh(d, a, b, c, x[i+12], 11, -421815835);
																c = md5_hh(c, d, a, b, x[i+15], 16,  530742520);
																b = md5_hh(b, c, d, a, x[i+ 2], 23, -995338651);

																a = md5_ii(a, b, c, d, x[i+ 0], 6 , -198630844);
																d = md5_ii(d, a, b, c, x[i+ 7], 10,  1126891415);
																c = md5_ii(c, d, a, b, x[i+14], 15, -1416354905);
																b = md5_ii(b, c, d, a, x[i+ 5], 21, -57434055);
																a = md5_ii(a, b, c, d, x[i+12], 6 ,  1700485571);
																d = md5_ii(d, a, b, c, x[i+ 3], 10, -1894986606);
																c = md5_ii(c, d, a, b, x[i+10], 15, -1051523);
																b = md5_ii(b, c, d, a, x[i+ 1], 21, -2054922799);
																a = md5_ii(a, b, c, d, x[i+ 8], 6 ,  1873313359);
																d = md5_ii(d, a, b, c, x[i+15], 10, -30611744);
																c = md5_ii(c, d, a, b, x[i+ 6], 15, -1560198380);
																b = md5_ii(b, c, d, a, x[i+13], 21,  1309151649);
																a = md5_ii(a, b, c, d, x[i+ 4], 6 , -145523070);
																d = md5_ii(d, a, b, c, x[i+11], 10, -1120210379);
																c = md5_ii(c, d, a, b, x[i+ 2], 15,  718787259);
																b = md5_ii(b, c, d, a, x[i+ 9], 21, -343485551);

																a = safe_add(a, olda);
																b = safe_add(b, oldb);
																c = safe_add(c, oldc);
																d = safe_add(d, oldd);
								}
								return Array(a, b, c, d);

}

/*
	* These functions implement the four basic operations the algorithm uses.
	*/
function md5_cmn(q, a, b, x, s, t)
{
								return safe_add(bit_rol(safe_add(safe_add(a, q), safe_add(x, t)), s),b);
}
function md5_ff(a, b, c, d, x, s, t)
{
								return md5_cmn((b & c) | ((~b) & d), a, b, x, s, t);
}
function md5_gg(a, b, c, d, x, s, t)
{
								return md5_cmn((b & d) | (c & (~d)), a, b, x, s, t);
}
function md5_hh(a, b, c, d, x, s, t)
{
								return md5_cmn(b ^ c ^ d, a, b, x, s, t);
}
function md5_ii(a, b, c, d, x, s, t)
{
								return md5_cmn(c ^ (b | (~d)), a, b, x, s, t);
}

/*
	* Calculate the HMAC-MD5, of a key and some data
	*/
function core_hmac_md5(key, data)
{
								var bkey = str2binl(key);
								if(bkey.length > 16) bkey = core_md5(bkey, key.length * chrsz);

								var ipad = Array(16), opad = Array(16);
								for(var i = 0; i < 16; i++)
								{
																ipad[i] = bkey[i] ^ 0x36363636;
																opad[i] = bkey[i] ^ 0x5C5C5C5C;
								}

								var hash = core_md5(ipad.concat(str2binl(data)), 512 + data.length * chrsz);
								return core_md5(opad.concat(hash), 512 + 128);
}

/*
	* Add integers, wrapping at 2^32. This uses 16-bit operations internally
	* to work around bugs in some JS interpreters.
	*/
function safe_add(x, y)
{
								var lsw = (x & 0xFFFF) + (y & 0xFFFF);
								var msw = (x >> 16) + (y >> 16) + (lsw >> 16);
								return (msw << 16) | (lsw & 0xFFFF);
}

/*
	* Bitwise rotate a 32-bit number to the left.
	*/
function bit_rol(num, cnt)
{
								return (num << cnt) | (num >>> (32 - cnt));
}

/*
	* Convert a string to an array of little-endian words
	* If chrsz is ASCII, characters >255 have their hi-byte silently ignored.
	*/
function str2binl(str)
{
								var bin = Array();
								var mask = (1 << chrsz) - 1;
								for(var i = 0; i < str.length * chrsz; i += chrsz)
																bin[i>>5] |= (str.charCodeAt(i / chrsz) & mask) << (i%32);
								return bin;
}

/*
	* Convert an array of little-endian words to a string
	*/
function binl2str(bin)
{
								var str = "";
								var mask = (1 << chrsz) - 1;
								for(var i = 0; i < bin.length * 32; i += chrsz)
																str += String.fromCharCode((bin[i>>5] >>> (i % 32)) & mask);
								return str;
}

/*
	* Convert an array of little-endian words to a hex string.
	*/
function binl2hex(binarray)
{
								var hex_tab = hexcase ? "0123456789ABCDEF" : "0123456789abcdef";
								var str = "";
								for(var i = 0; i < binarray.length * 4; i++)
								{
																str += hex_tab.charAt((binarray[i>>2] >> ((i%4)*8+4)) & 0xF) +
																								hex_tab.charAt((binarray[i>>2] >> ((i%4)*8  )) & 0xF);
								}
								return str;
}

/*
	* Convert an array of little-endian words to a base-64 string
	*/
function binl2b64(binarray)
{
								var tab = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
								var str = "";
								for(var i = 0; i < binarray.length * 4; i += 3)
								{
																var triplet = (((binarray[i   >> 2] >> 8 * ( i   %4)) & 0xFF) << 16)
																								| (((binarray[i+1 >> 2] >> 8 * ((i+1)%4)) & 0xFF) << 8 )
																								|  ((binarray[i+2 >> 2] >> 8 * ((i+2)%4)) & 0xFF);
																for(var j = 0; j < 4; j++)
																{
																								if(i * 8 + j * 6 > binarray.length * 32) str += b64pad;
																								else str += tab.charAt((triplet >> 6*(3-j)) & 0x3F);
																}
								}
								return str;
}
function peng()
{
	print(hex_md5("xiepeng"));
}
