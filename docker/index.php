<?php

class mcrypt{
    private $key = "";
    private $key_size = 0;
    private $iv = "";
    private $iv_size = 0;
    private $ciphertext = "";
    private $ciphertext_dec = "";

    public function __construct($str,$key){
        if ( !empty($str) ){
            $this->encrypt($str,!empty($key)?$key:"");
        }
    }

    public function get_ciphertext(){
        return $this->ciphertext;
    }
    public function get_ciphertext_dec(){
        return $this->ciphertext_dec;
    }
    public function set_iv(){
        # 为 CBC 模式创建随机的初始向量
        $this->iv_size = mcrypt_get_iv_size(MCRYPT_RIJNDAEL_128, MCRYPT_MODE_CBC);
        $this->iv = mcrypt_create_iv($this->iv_size, MCRYPT_RAND);
    }
    public function get_key_size(){
        return $this->key_size;
    }
    public function set_key($key){
        if(empty($key)){
            $this->key = pack('H*', "wackhappyhacking");
        }else{
            $this->key = $key;
        }
    }
    public function get_key(){
        return $this->key;
    }

    # --- 加密 ---
    # 密钥应该是随机的二进制数据，
    # 开始使用 scrypt, bcrypt 或 PBKDF2 将一个字符串转换成一个密钥
    # 密钥是 16 进制字符串格式
    # === 警告 ===
    # 密文并未进行完整性和可信度保护，
    # 所以可能遭受 Padding Oracle 攻击。

    public function encrypt($str,$key){
        $this->set_key($key);
        # 显示 AES-128, 192, 256 对应的密钥长度：
        #16，24，32 字节。
        $this->key_size =  strlen($this->key);
        $this->set_iv();
        # 创建和 AES 兼容的密文（Rijndael 分组大小 = 128）
        # 仅适用于编码后的输入不是以 00h 结尾的
        # （因为默认是使用 0 来补齐数据）
        $this->ciphertext = mcrypt_encrypt(MCRYPT_RIJNDAEL_128, $this->get_key(),
                                     $str, MCRYPT_MODE_CBC, $this->iv);

        # 将初始向量附加在密文之后，以供解密时使用
        $this->ciphertext = $this->iv . $this->ciphertext;
        # 对密文进行 base64 编码
        $this->ciphertext = base64_encode($this->ciphertext);
        return $this;
    }
    # --- 解密 ---
    public function decrypt($str,$key){
        $this->set_key($key);
        # 显示 AES-128, 192, 256 对应的密钥长度：
        #16，24，32 字节。
        $this->key_size =  strlen($this->get_key());
        $this->set_iv();

        $this->ciphertext_dec = base64_decode($str);

        # 初始向量大小，可以通过 mcrypt_get_iv_size() 来获得
        $iv_dec = substr( $this->ciphertext_dec, 0, $this->iv_size);

        # 获取除初始向量外的密文
        $this->ciphertext_dec = substr( $this->ciphertext_dec, $iv_size);

        # 可能需要从明文末尾移除 0
        $this->ciphertext_dec = mcrypt_decrypt(MCRYPT_RIJNDAEL_128, $this->get_key(),
                                               $this->ciphertext_dec, MCRYPT_MODE_CBC, $iv_dec);

        return $this;
    }
}


$plaintext = "wackonlineispassword";

//$p = new mcrypt($plaintext);
//var_dump($p);
//echo $p->get_ciphertext()."<br />";
var_dump(getenv("MYSQL_1_PORT_3306_TCP_ADDR"));
//exit();
$mysqli = new mysqli(getenv("MYSQL_1_PORT_3306_TCP_ADDR"), "root", "wackonline", "helloworld");

/* check connection */
if ($mysqli->connect_errno) {
    printf("Connect failed: %s\n", $mysqli->connect_error);
    exit();
}
var_dump($_GET,$mysqli->server_info,$mysqli);
echo "<hr />";
$create_table =
              'CREATE TABLE IF NOT EXISTS `wack_user`
              (
                   id INT(10) NOT NULL AUTO_INCREMENT,
                   username VARCHAR(100) NOT NULL,
                   password VARCHAR(255) NOT NULL,
                   PRIMARY KEY(id)
              )';
if(isset($_GET['step']) && $_GET['step'] == 'create'){
    $table = $mysqli->query($create_table);
    echo "<br /> table created: ".$table."<br />";
    /* set autocommit to off */
    $mysqli->autocommit(FALSE);

    /* Insert some values */
    $mysqli->query("INSERT INTO `wack_user` VALUES ('', 'wack', 'wack')");
    $mysqli->query("INSERT INTO `wack_user` VALUES ('', 'admin', 'admin')");

    /* commit transaction */
    $mysqli->commit();

    printf("%s\n", $mysqli->info);
}else{
    echo "<hr />";
    //$id=rand(1,100);
    //$query = "INSERT INTO `wack_user` VALUES (NULL, 'admin{$id}', 'admin{$id}')";
    //$mysqli->query($query);

    //printf ("New Record has id %d.\n", $mysqli->insert_id);

    $result = $mysqli->query("select * from `wack_user`");
    //$data = $result->fetch_array(MYSQLI_ASSOC);
    while($data = $result->fetch_object()){
        echo "id: ".$data->id." username: ".$data->username." password: ".$data->password."<br />";
    }

    echo "<br />field_count: ".$mysqli->field_count;
}


$mysqli->close();



echo "<html>
<head>
	<title>test pages....</title>
</head>
<body><br />".
time()."
</br>
<hr />
".date("Y-m-d H:i:s",time())."
</body>
</html>";
?>
