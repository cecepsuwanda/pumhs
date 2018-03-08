<?PHP
    if (isset($_POST["btnSubmit"])) {
		session_start();
		$_SESSION["usr"] = "root";
		require_once "connect_db.php";
		
        $username    = mysql_real_escape_string($_POST["userName"]);
		
        $password    = md5($_POST["password"]);
        $sql    = "SELECT * 
				  FROM tmst_admin WHERE user='".$username."'";
        
        $hasil    = mysql_query($sql);
        if ($hasil) {		
            //masuk kalo query berhasil dieksekusi
            $data    = mysql_fetch_object($hasil);
            if ($data) {
                if ($password == $data -> pass) {
					//session_start();
                    $_SESSION["userName"] = $username;
					$_SESSION["password"] = $password;
					$_SESSION["lg_time"] = date("Y-m-d H:i:s");
					
					$sql    = "insert into admin_log(lg_time,user) value('".$_SESSION["lg_time"]."','".$_SESSION["userName"]."')";
					mysql_query($sql);
					
					?>
					<script>
					      window.location="list.php"; 
					</script>
					<?php
                }
                else {
					$_SESSION['userName'] = $username;
					$_SESSION['_message'] = "password_salah";
					?>
					<script>
						 window.location="index.php"; 
					</script>
					<?php
                }
            }
            else {
				$_SESSION['userName'] = $username;
				$_SESSION['_message'] = "user_tidak_terdaftar";
				
				?>
				<script>
					window.location="index.php"; 
				</script>
				<?php
            }
        }
        else echo "Query salah";
    }
    else {$_SESSION['_message'] = "user_tidak_terdaftar";};
?>