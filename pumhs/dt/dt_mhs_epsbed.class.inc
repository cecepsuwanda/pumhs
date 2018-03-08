<?php
require_once dirname(dirname(dirname(__FILE__))).'/shared.php';

class dt_mhs_epsbed
{
   var $tb;
   var $numrows;  
   
 
   
   function __construct(){
     $this->tb = new tb_epsbed_mhs;
	 
   }
     
	 function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function is_exist($nim,$nama)
    {
      $data = $this->tb->getData("nimhsmsmhs='".$nim."' and nmmhsmsmhs='".$nama."'");	 
	  
	  return $this->tb->numrows>=1;	  
	}
	
	
}
?>


 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 