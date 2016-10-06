/*
@title: Cartesian Tree �ѿ�����
@description:
    Cartesian Tree �ѿ�����
    ����ʵ������ʱ���ڽ�������BST���ʵ���
@structure:
    CartesianTreeNode:
        parent:����ָ��
        l: ����ָ��
        r: �Һ���ָ��
@arguments:
    BuildFromArray:
        value: Դ����
        N: �����С
        index: Դ�������ӳ������
        tree: Ŀ�꽨�������ڴ��׵�ַ
        stack: ��ջ�ռ�
@performance:
    BuildFromArray:
        Time: O(N)
        Space: O(N)
@dependence: null
@range:
    for i in [0, N)
    value[i] in [0, N)
    index[i] in [0, N)
    |value| = |index| = |tree| = |stack| = N
@note:
    value �� index ��Ϊ��ӳ�������˫������
        index[value[i]] == i
        value[index[i]] == i
    index �����ں������ʼ�����������̿��Լ��� index
    stack �����ں������ʼ�������������̶� stack ����Ⱦ
    ������������ʱ��ջ��һ��Ϊ value[0]
    �ѿ�����������һ��Ϊ value[0]
    ��˵ѿ������� parent ��һ��Ҫ���棬�����溢��ָ��Ҳ������ɱ���
*/

struct CartesianTreeNode {
  int parent, left, right;
};

void BuildFromArray(int *value, int N, int *index, CartesianTreeNode *tree,
                    int *stack) {
  // ������ӳ��
  for (int i = 0; i < N; i++) {
    index[value[i]] = i;
  }
  // ��ʼ���ڵ�
  for (int i = 0; i < N; i++) {
    tree[i].parent = tree[i].left = tree[i].right = -1;
  }
  int size = 0; // ��ʼ�����ջ
  for (int i = 0; i < N; i++) {
    int nextSize = size;
    // ά������ջ
    while (nextSize > 0 && index[stack[nextSize - 1]] > index[i]) {
      nextSize--;
    }
    // �������� if �����˳��ɱ�
    if (nextSize > 0) { // ջ����Ԫ��
      // ��ǰԪ��Ϊջ��Ԫ�ص��Һ���
      int top = stack[nextSize - 1];
      tree[i].parent = top;
      tree[top].right = i;
    }
    if (nextSize < size) { // ����ջ
      // ����ջ��Ԫ��Ϊ��ǰԪ�ص�����
      int lastPop = stack[nextSize];
      tree[lastPop].parent = i;
      tree[i].left = lastPop;
    }
    stack[nextSize++] = i; // ��ջ
    size = nextSize;       // ����ջ��С
  }
}

