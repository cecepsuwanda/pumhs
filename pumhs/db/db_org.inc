<?php

Class DbConnect { 
             
                  var $host = 'localhost'; 
                  var $user = 'root'; 
                  var $password = ''; 
                  var $database = 'pumhs'; 
                  var $persistent = false; 
                   
                  var $conn = NULL; 
                   
                  var $result= false; 
                  var $error_reporting = false; 
                   
      /*constructor function this will run when we call the class */ 
       
                  function __construct($host, $user, $password, $database, $error_reporting=true, $persistent=false) { 
                       
                     if( !empty($host) and !empty($user) and !empty($password) and !empty($database)){
 					   $this->host = $host; 
                       $this->user = $user; 
                       $this->password = $password; 
                       $this->database = $database; 
                      }else{
					     
						 $server = $_SERVER['DOCUMENT_ROOT'];
                         $base_path = $server ;
						 
                         if($base_path<>"C:/xampp/htdocs/pumhs"){						    
                            $this->host = 'localhost'; 
                            $this->user = 'uni10000_admin'; 
                            $this->password = 'bismillah2013'; 
                            $this->database = 'uni10000_pumhs';					    
						 }
					  }
					  
					   $this->persistent = $persistent; 
                       $this->error_reporting = $error_reporting; 
                  } 
    
              function open() { 
                   
                  if ($this->persistent) { 
                             
                        $func = 'mysql_pconnect'; 
                   
                  } else { 
                       
                     $func = 'mysql_connect'; 
                      
                  }             
                   set_time_limit(0);
                  /* Connect to the MySQl Server */ 
                   
                  $this->conn = $func($this->host, $this->user, $this->password); 
                   
                   if (!$this->conn) { 

                       return false; 
                   
                   } 
                   
                   /* Select the requested DB */ 
                   
                   if (@!mysql_select_db($this->database, $this->conn)) { 
                        
                       return false; 
                   } 
                     return true; 
              } 
    
              /*close the connection */ 
               
               function close() { 
                       
                   return (@mysql_close($this->conn)); 
               } 
    
                /* report error if error_reporting set to true */ 
                 
      function error() { 
             
          if ($this->error_reporting) { 
                 
              return (mysql_error()) ; 
          } 
           
      } 
      
       function query($sql) { 
                
             $this->result = @mysql_query($sql, $this->conn); 
         
        return($this->result != false); 
        
       } 
    function affectedrows() { 

        return(@mysql_affected_rows($this->conn)); 
    } 
     
    function numrows() { 
         
        return(@mysql_num_rows($this->result)); 
         
    } 
    function fetchobject() { 
         
         return(@mysql_fetch_object($this->result, MYSQL_ASSOC)); 
         
    } 
     function fetcharray() { 
          
          return(mysql_fetch_array($this->result)); 
          
     } 
      
	 function fetchrow() { 
          
          return(mysql_fetch_row($this->result)); 
          
     }  
	  
     function fetchassoc() { 
          
         return(@mysql_fetch_assoc($this->result)); 
     } 
      
     function freeresult() { 
          
          return(@mysql_free_result($this->result)); 
          
     } 
         
   } 
?>