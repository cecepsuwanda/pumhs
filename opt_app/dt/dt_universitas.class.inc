<?php
   require_once dirname(dirname(__FILE__)).'/shared.php'; 
class dt_universitas
{
   var $tb;
   var $numrows;  
  
   function __construct(){
     $this->tb = new tb_universitas;
	 
   }
  
	function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	
	
}
?>