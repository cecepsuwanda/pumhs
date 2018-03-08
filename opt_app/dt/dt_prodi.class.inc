<?php

 require_once dirname(dirname(__FILE__)).'/shared.php'; 
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

	function getnmprodi($kd_fak,$kd_prodi)
	{
      $data = $this->getData("kd_fakultas='".$kd_fak."' and kd_prodi='".$kd_prodi."'");
      $nm = $data[0]['prodi'];
      return $nm;
	}
	
   
    function getdropprodi($kd_fak)
    {
      $prodi = $this->get_prodi($kd_fak);
      $txt="";

      if(!empty($prodi)){
         foreach ($prodi as $k=>$v) {
         	$txt.="<option value=".$K." >".$v."</option>";
         }
      }

      return $txt; 
    }

    function get_prodi($kd_fak)
	{
      $data = $this->getData("kd_fakultas='".$kd_fak."'");

      $prodi = array();
      if(!empty($data)){
         foreach ($data as $r) {
         	$prodi[$r['kd_prodi']] = $r['prodi'];
         }
      }

      return $prodi;

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