<?php
/**
 * Copyleft (C) 2012  
 * @author "B.Tag" <bb.anyd@gmail.com>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of	
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

// Iterative ergodic character coding
// if ord () > 0xa0 substr($str, $i, 2)

function cnsubstr($str,$start,$len){

	$tmpstr = "";
	$strlens = $start + $len;
	for($i = 0; $i < $strlens; $i++) {
		if(ord(substr($str, $i, 1)) > 0xa0) {
			$tmpstr .= substr($str, $i, 2);
			$i++;
		} else
			$tmpstr .= substr($str, $i, 1);
	}
	return $tmpstr;
}


///echo cnsubstr("我的主页http://www.boolsir.com,操!垃圾信息，哈哈哈大师级点卡第三届很多出色卡号",41);

function cnsubstr1($str,$strlen=10) {
  if(empty($str)||!is_numeric($strlen)){
    return false;
  }
  if(strlen($str)<=$strlen){
    return $str;
  }

  $last_word_needed=substr($str,$strlen-1,1);
  if(!ord($last_word_needed)>160){
    $needed_sub_sentence=substr($str,0,$strlen);
    return $needed_sub_sentence;
  }else{
    for($i=0;$i<=$strlen;$i++){
      if(ord($str[$i])>160){
	$i++;
      }
    }
    echo $i;$needed_sub_sentence=substr($str,0,$i);
    return $needed_sub_sentence;
  }
}

///echo cnsubstr1("我的主页http://www.boolsir.com,操!垃圾信息，哈哈哈大师级点卡第三届很多出色卡号",54);	

/*
Utf-8、gb2312都支持的汉字截取函数
cut_str(字符串, 截取长度, 开始长度, 编码);
编码默认为 utf-8
开始长度默认为 0
*/

function cut_str($string, $sublen, $start = 0, $code = 'UTF-8')
{
    if($code == 'UTF-8')
    {
      return preg_replace('#^(?:[\x00-\x7F]|[\xC0-\xFF][\x80-\xBF]+){0,'.$start.'}'.
                       '((?:[\x00-\x7F]|[\xC0-\xFF][\x80-\xBF]+){0,'.$sublen.'}).*#s',
                       '$1',$str);
      /*
	$pa = "/[\x01-\x7f]|[\xc2-\xdf][\x80-\xbf]|\xe0[\xa0-\xbf][\x80-\xbf]|[\xe1-\xef][\x80-\xbf][\x80-\xbf]|\xf0[\x90-\xbf][\x80-\xbf][\x80-\xbf]|[\xf1-\xf7][\x80-\xbf][\x80-\xbf][\x80-\xbf]/";
        preg_match_all($pa, $string, $t_string);
        if(count($t_string[0]) - $start > $sublen) return join('', array_slice($t_string[0], $start, $sublen))."...";
        return join('', array_slice($t_string[0], $start, $sublen));
      */
    }
    else
    {
        $start = $start*2;
        $sublen = $sublen*2;
        $strlen = strlen($string);
        $tmpstr = '';

        for($i=0; $i< $strlen; $i++)
        {
            if($i>=$start && $i< ($start+$sublen))
            {
                if(ord(substr($string, $i, 1))>0xa0)
                {
                    $tmpstr.= substr($string, $i, 2);
                }
                else
                {
                    $tmpstr.= substr($string, $i, 1);
                }
            }
            if(ord(substr($string, $i, 1))>0xa0) $i++;
        }
        if(strlen($tmpstr)< $strlen ) $tmpstr.= "...";
        return $tmpstr;
    }
}

$str = "职位描述：
1.对所编写的PHP程序进行严格的综合测试，进行系统故障的诊断、定位、分析和调试，以实施产品测试方案. 
2.根据开发进度和任务分配，完成相应模块软件的设计、开发、编程任务
3.在整个公司监督下定期完成量化的工作要求。
4.有很高的职业道德操守，有很强的团队意识。
任职要求：
1.计算机相关专业专科以上学历； 
2.二年以上PHP/MYSQL/Apache开发经验，具有良好的编程风格； 
3.熟悉smarty模板引擎技术，Jquery框架，了解MVC模形，能完成网站的第二次开发，熟悉ajax技术，熟练使用javascript，CSS，SQL； 
4.有开发过大中型互联网站经验者优先；
5.熟悉 Web 2.0，了解电子商务行业优先；，";
echo cut_str($str, 160, 0, 'UTF-8');

function utf8Substr($str, $from, $len)
{
    return preg_replace('#^(?:[\x00-\x7F]|[\xC0-\xFF][\x80-\xBF]+){0,'.$from.'}'.
                       '((?:[\x00-\x7F]|[\xC0-\xFF][\x80-\xBF]+){0,'.$len.'}).*#s',
                       '$1',$str);
}
echo "<br>".utf8Substr($str,0,146);
?>
