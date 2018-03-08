<?php

require_once dirname(dirname(__FILE__)).'/shared.php';

$dt = new dt_guestbook;
$data = $dt->getData("");
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
	<head><meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
        
        <meta name="language" content="en">

        <!-- blueprint CSS framework -->
        <link rel="stylesheet" type="text/css" href="../css/screen.css" media="screen, projection">
        <link rel="stylesheet" type="text/css" href="../css/print.css" media="print">
        <!--[if lt IE 8]>
        <link rel="stylesheet" type="text/css" href="/css/ie.css" media="screen, projection" />
        <![endif]-->
        <link rel="stylesheet" href="../css/css.css">
        <link rel="stylesheet" type="text/css" href="../css/main.css">
        <link rel="stylesheet" type="text/css" href="../css/form.css">
        <link rel="stylesheet" href="../css/select2.css">
        <link rel="icon" type="image/png" href="../image/unibbaicon.png">
        
		<title>PUMHS - Guestbook</title>
		
		
		
		
    </head>
<body>



<div class="container" id="page">
<div id="header">
    <a href="http://www.unibba.ac.id/">
        <img src="../image/header3.png" height="110" width="1000">
    </a>
</div><!-- header -->
<div id="content">
<table width="400" border="0" align="center" cellpadding="0" cellspacing="1" bgcolor="#CCCCCC">
<tr>
<form id="form1" name="form1" method="post" action="addguestbook.php">
<td>
<table width="400" border="0" cellpadding="3" cellspacing="1" bgcolor="#FFFFFF">
<tr>
<td width="117">Name</td>
<td width="14">:</td>
<td width="357"><input name="name" type="text" id="name" size="40" /></td>
</tr>
<tr>
<td>Email</td>
<td>:</td>
<td><input name="email" type="text" id="email" size="40" /></td>
</tr>
<tr>
<td valign="top">Comment</td>
<td valign="top">:</td>
<td><textarea name="comment" cols="40" rows="3" id="comment"></textarea></td>
</tr>
<tr>
<td>&nbsp;</td>
<td>&nbsp;</td>
<td><input type="submit" name="Submit" value="Submit" /> <input type="reset" name="Submit2" value="Reset" /></td>
</tr>
</table>
</td>
</form>
</tr>
</table>
<br>
<?php
foreach($data as $rows){
$pattern = '#<([A-Za-z][A-Za-z0-9]*)\b[^>]*>(.*?)</([A-Za-z][A-Za-z0-9]*)\b[^>]*>#';
$pattern1 = '#http://#';
$pattern2 = '#\b(the|are|am|is|a|of|to)\b#';
$pattern3 = '#(outlet[a-z]{5}|roulette|blackjack|poker|slots|slot|azart|[ck]a[sz]ino|Brhypozydor|AKemaUnale)#';
if(($rows['comment']!='') and ((preg_match($pattern,$rows['comment'])==0) and (preg_match($pattern1,$rows['comment'])==0) and (preg_match($pattern2,$rows['comment'])==0) and (preg_match($pattern3,$rows['name'])==0) )){
?>

<table width="400" border="0" align="center" cellpadding="0" cellspacing="1" bgcolor="#CCCCCC">
<tr>
<td><table width="400" border="0" cellpadding="3" cellspacing="1" bgcolor="#FFFFFF">
<tr>
<td>ID</td>
<td>:</td>
<td><?php echo $rows['id']; ?></td>
</tr>
<tr>
<td width="117">Name</td>
<td width="14">:</td>
<td width="357"><?php echo $rows['name']; ?></td>
</tr>
<tr>
<td>Email</td>
<td>:</td>
<td><?php echo $rows['email']; ?></td>
</tr>
<tr>
<td valign="top">Comment</td>
<td valign="top">:</td>
<td><?php echo $rows['comment']; ?></td>
</tr>
<tr>
<td valign="top">Date/Time </td>
<td valign="top">:</td>
<td><?php echo $rows['datetime']; ?></td>
</tr>
</table></td>
</tr>
</table>

<?php
 }else{
  $dt->delete($rows['id']);
 }
}
//mysql_close(); //close database
?>

</div><!-- content -->
<div class="clear"></div>

<div id="footer">
<p>
Jalan RAA. Wiranatakusuman No. 7 Bale Endah Bandung <br>
Telepon (022) 594 0443, 594 0262, 594 7087 <br>
Fax (022) 594 0443 <br>
Situs <a href="http://www.unibba.ac.id/">www.unibba.ac.id</a> <br><br>

© PUMHS Pendataan Ulang Mahasiswa 2013 <br>
<!--Copyright &copy; 2013 by FTI Unibba<br/>
All Rights Reserved.<br/>
-->
</p>
</div><!-- footer -->
</div><!-- page -->
</body>
</html>