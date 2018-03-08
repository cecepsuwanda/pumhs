<?php
  require_once dirname(dirname(__FILE__)).'/shared.php'; 
class dt_admin_log
{
   var $tb;
   var $numrows;  
  
   function __construct(){
     $this->tb = new tb_admin_log;
	 
   }
  
	function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function logout($lg_time,$id)
   {       
	   $this->tb->updateRecord(array('lg_time'=>$lg_time,'user'=>$id,'out_time'=>date("Y-m-d H:i:s")));
	   return 1;
   }
	
	
}
?>