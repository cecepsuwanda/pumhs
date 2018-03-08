<?php 
 require_once dirname(dirname(dirname(__FILE__))).'/shared.php';
class dt_fak
{
   var $tb;
   var $numrows;  
  
   function __construct(){
     $this->tb = new tb_fak;
	 
   }
  
	function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	
	
}
?>