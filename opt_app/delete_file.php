<?php 

require_once("shared.php");

$nm = $_POST['nm'];
$id_opt = isset($_SESSION["id_opt"]) ? $_SESSION["id_opt"] : "";

if(file_exists($nm)){ 
  $dt_opt_ctk_log = new dt_opt_ctk_log;
  $dt_mhs = new dt_mhs;
  
  $file = basename($nm);
  $dt_opt_ctk_log->delete($file,$id_opt);
  
  $file = basename($nm, ".pdf"); // $file is set to "index"
  if(strpos($file,'Form Verifikasi')!== false )
  {   
	$tgl=date("Y-m-d H:i:s");
    $dt_mhs->kosongkan_nm_file($file,$tgl,$id_opt);
  } 
  unlink($nm);
}			

?>