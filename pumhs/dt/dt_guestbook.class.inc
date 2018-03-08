<?php
require_once dirname(dirname(dirname(__FILE__))).'/shared.php';
class dt_guestbook
{
   var $tb;
   var $numrows;  
  
   function __construct(){
     $this->tb = new tb_guestbook;
	 
   }
  
	function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function delete($id)
	{
	   $data = $this->tb->deleteRecord(array("id"=>$id));
	   return 0; 
	}
	
}
?>