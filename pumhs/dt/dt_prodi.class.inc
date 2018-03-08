<?php
 require_once dirname(dirname(dirname(__FILE__))).'/shared.php';
class dt_prodi
{
   var $tb;
   var $numrows;  
  
   function __construct(){
     $this->tb = new tb_prodi;
	 
   }
  
	function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function get_fak($kd_prodi)
	{
	   $fak="";
	   $data=$this->getData("kd_prodi='".$kd_prodi."'");
	   if(!empty($data)){
	    foreach($data as $row){
		  $fak=$row['kd_fakultas'];
		}	  
	  }  
	   return $fak;
	}
	
}
?>