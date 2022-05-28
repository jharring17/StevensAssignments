(**************************************************************************************************
* Name          : gt.ml 
* Author        : Jack Harrington 
* Date          : February 21, 2022
* Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
* Description   : Basic general tree operations in Ocaml.
**************************************************************************************************)

(* General Trees Notes:
Example:
            33
          /    \
         12      77
                / | \ 
              37 48  103
              |
              14
*)

(* General Tree Type Definition *)
type 'a gt = Node of 'a * ('a gt) list

(* Testing Trees *)
let t : int gt = 
    Node (33, 
        [Node (12, []);
         Node (77, 
            [Node (37, 
                [Node (14, [])]);
            Node (48, []);
            Node (103, [])])
        ])

let t2 : int gt = 
    Node (33, [])

let t3 : int gt = 
    Node (33, [Node (12, [])])

(* Sample Tree Building Function *)
let mk_leaf (n: 'a) : 'a gt = (* 'a -> 'a gt = <fun> *)
    Node(n,[])

(* Max Helper Function *)
let rec max l x = (* 'a list -> 'a -> 'a = <fun> *)
  match l with
  | [] -> x
  | h::t -> if h>x then max t h else max t x

(* Height Function *)
let rec height t = (* 'a gt -> int = <fun> *)
    match t with 
    | Node(n, []) -> 1
    | Node(n, l) -> max(List.map height l) 0 + 1

(* Size Function *)
let rec size t = (*'a gt -> int = <fun> *)
    match t with
    | Node (n, []) -> 1
    | Node (n,l) -> 1 + List.fold_left (fun x y -> x + y) 0 (List.map size l)

(* Path_to_leaves Function *)
let rec paths_to_leaves t = (* 'a gt -> int list list = <fun> *)
  match t with
  | Node (n, []) -> [[]]
  | Node (n, l) -> List.flatten (List.mapi (fun i n -> (List.map (fun x -> i :: x) n)) 
                    (List.map paths_to_leaves l))

(* perfectHelper Function *)
let rec perfectHelper l = (* 'a list list -> bool = <fun> *)
    match l with
    |[] -> true
    |h::t when t = [] -> true
    |h::t when (List.length h) != (List.length (List.hd t)) -> false
    |h::t -> perfectHelper t

(* is_leaf_perfect Function *)
let is_leaf_perfect t = (* 'a gt -> bool = <fun> *)
    perfectHelper (paths_to_leaves t)

(* Preorder Function *)
let rec preorder t = (* 'a gt -> 'a list = <fun> *)
  match t with
  | Node(n, []) -> [n]
  | Node(n, leaf) -> n :: List.concat(List.map preorder leaf)

(* Mirror Function *)
let rec mirror t = (* 'a gt -> 'a gt = <fun> *)
    match t with
    | Node (n, []) -> Node (n, [])
    | Node (n, l) -> Node (n, List.map mirror (List.rev l))

(* Mapt Function *)
let rec mapt t (Node(n, l)) =  (* ('a -> 'b) -> 'a gt -> 'b gt = <fun> *)
  Node(t n, List.map (mapt t) l)

(* Foldt Function *)
let rec foldt f (Node(n, l)) = (* ('a -> 'b list -> 'b) -> 'a gt -> 'b = <fun> *)
  match (Node(n, l)) with
  | Node(n, l) -> f n (List.map (foldt f) l)

(* Mirror' Function *)
let mirror' t = (* 'a gt -> 'a gt = <fun> *)
  foldt (fun n revl -> Node(n, (List.rev) revl)) t