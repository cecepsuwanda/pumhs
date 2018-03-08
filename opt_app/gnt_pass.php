<?php

require_once 'shared.php';

$pass_lama = md5($_POST['lama']);
$pass_baru = md5($_POST['baru']);
$id_opt = isset($_SESSION["id_opt"]) ? $_SESSION["id_opt"]: '';

        $dt_operator = new dt_operator;		
		
	  if($dt_operator->cekpass($id_opt,$pass_lama))
	  {	
		if($dt_operator->ubahpass($id_opt,$pass_baru))
		{
		  echo "Password Berhasil di Ganti !!! ";
		}else{
		
		  echo "Password Gagal di Ganti !!! ";
		}
	  }else{
	    echo "Password Lama Salah !!! ";
	  }	

?>