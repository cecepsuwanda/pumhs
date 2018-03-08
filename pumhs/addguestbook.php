<?php

require_once dirname(dirname(__FILE__)).'/shared.php';

$datetime=date("y-m-d h:i:s"); //date time

$name = $_POST['name'];
$email = $_POST['email'];
$comment = $_POST['comment'];
$pattern = '#<([A-Za-z][A-Za-z0-9]*)\b[^>]*>(.*?)</([A-Za-z][A-Za-z0-9]*)\b[^>]*>#';
$pattern1 = '~/(\%27)|(\')|(\-\-)|(\%23)|(#)/ix~';
if((preg_match($pattern,$comment)==0) and (preg_match($pattern1,$comment)==0)){
 $tb_guestbook = new tb_guestbook;
 $tb_guestbook->insertRecord(array('name'=>$name, 'email'=>$email, 'comment'=>$comment, 'datetime'=>$datetime));
}
?>
 <script>
window.location="viewguestbook.php";
</script>