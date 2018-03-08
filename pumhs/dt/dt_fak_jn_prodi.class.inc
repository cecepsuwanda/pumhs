<?php
require_once dirname(dirname(dirname(__FILE__))).'/shared.php';
class dt_fak_jn_prodi
{
   var $tb;
   var $numrows;  
   var $idx_fk;
   var $idx_prd;
     
   function __construct(){
     $this->idx_fk = array();
	 $this->idx_prd = array();
	 	 
	 $this->tb = new tb_fak_jn_prodi;
	 
     $data = $this->getData("");
	 
	 if(!empty($data))
	 {
	   foreach($data as $row)
	   {
	     $this->idx_fk[$row['kd_fakultas']]['nm_fak']=$row['fakultas'];
		 $this->idx_fk[$row['kd_fakultas']]['prodi'][$row['kd_prodi']]['nm_prodi']=$row['prodi'];
		 $this->idx_prd[$row['kd_prodi']]['nm_prodi']=$row['prodi'];
		 $this->idx_prd[$row['kd_prodi']]['kd_fak']=$row['kd_fakultas'];
		 $this->idx_prd[$row['kd_prodi']]['nm_fak']=$row['fakultas'];
	   } 
	 
	 }
	 
   
   }
  

	function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function getnmfk($kd_prodi)
    { 
	  $hsl=array();
	  if(isset($this->idx_prd[$kd_prodi]))
      {	   
		$hsl['kd_fak']=$this->idx_prd[$kd_prodi]['kd_fak'];
	    $hsl['nm_fak']=$this->idx_prd[$kd_prodi]['nm_fak'];
	  }else
	  {
	    $hsl['kd_fak']="";
	    $hsl['nm_fak']="Tidak Diisi";
	  }
	  return $hsl; 
	}
	
	
	
}
?>