<?php
 require_once dirname(dirname(__FILE__)).'/shared.php'; 
class dt_operator
{
   var $tb;
   var $numrows;
   var $id_opt;
   var $kd_fakultas; 
  
   function __construct(){
     $this->tb = new tb_operator;
	 
   }
  
	function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function ubahpass($id_opt,$pass)
	{
	  $this->tb->updateRecord(array("id_opt"=>$id_opt,"pass"=>$pass));
	  $this->getData("id_opt = '".$id_opt."' and pass='".$pass."'");
	  
	  return $this->numrows>0;
	}
	
	function cekuser($user)
	{
	  $data=$this->getData("user = '".$user."'");
	  $this->id_opt = $data[0]['id_opt'];
	  $this->kd_fakultas = $data[0]['kd_fakultas'];
	  return $this->numrows>0;
	}

	function cekpass($id_opt,$pass)
	{
	  $data=$this->getData("id_opt = '".$id_opt."' and pass='".$pass."'");	  
	  return $this->numrows>0;
	}
	
}
?>